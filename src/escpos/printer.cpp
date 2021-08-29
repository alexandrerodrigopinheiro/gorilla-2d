#include "../../includes/escpos/printer.h"

g2d::escpos::printer* g2d::escpos::printer::static_instance = nullptr;

#define VENDOR_ID	0x0416 // 0x04b8 // 0x090c
#define PRODUCT_ID	0x5011 // 0x0e15 // 0x1000

g2d::escpos::printer::printer()
	: _context(nullptr)
	, _printer(nullptr)
{
	int res; // for return values.
	libusb_device **devs;

	// initialize a library session.
	res = libusb_init(&this->_context);

	if (res < 0)
	{
		// there was an error.
		std::cerr << "Initialize error " << res << std::endl;

		exit(EXIT_FAILURE);
	}

	// set verbosity level to 3, as suggested in the documentation.
	libusb_set_option(this->_context, LIBUSB_OPTION_LOG_LEVEL);

	std::size_t count = libusb_get_device_list(this->_context, &devs);

    if (count <= 0)
    {
        std::cerr << "Cannot find devices" << std::endl;

        exit(EXIT_FAILURE);
    }

	libusb_device* device = nullptr;
	libusb_device_descriptor desc;

	for (std::size_t idx = 0; idx < count; ++idx)
	{
		device = devs[idx];
		desc = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		res = libusb_get_device_descriptor(device, &desc);

	    if (res != 0)
	    {
	        std::cerr << "Cannot get devices" << std::endl;

	        exit(EXIT_FAILURE);
	    }

	    std::string vendor_id = g2d::basic::to_hex_string(desc.idVendor, 4);
		std::string product_id = g2d::basic::to_hex_string(desc.idProduct, 4);

	    // these are vendorID and productID I found for my usb device.
	    this->_printer = libusb_open_device_with_vid_pid(this->_context, desc.idVendor, desc.idProduct);

	    if (this->_printer != nullptr)
	    {
			std::clog << "Open thermal printer vendor ID: " << vendor_id << " product ID: " << product_id << ", OK." << std::endl;

	    	break;
	    }
	}

    // find out if kernel driver is attached.
	res = libusb_kernel_driver_active(this->_printer, 0);

    if (res == 1)
    {
        std::clog << "Kernel Driver Active" << std::endl;

        // detach it.
        res = libusb_detach_kernel_driver(this->_printer, 0);

        if(res == 0)
        {
            std::clog << "Kernel Driver Detached!" << std::endl;
        }
    }

    // claim interface 0 (the first) of device (mine had jsut 1).
    res = libusb_claim_interface(this->_printer, 0);

    if (res < 0)
    {
        std::cerr << "Cannot Claim Interface" << std::endl;

        exit(EXIT_FAILURE);
    }
}

g2d::escpos::printer::~printer()
{
	// release the claimed interface.
	int res = libusb_release_interface(this->_printer, 0);

	if (res != 0)
	{
		std::clog << "Cannot Release Interface" << std::endl;
	}
	else
	{
		std::clog << "Released Interface" << std::endl;
	}

	libusb_close(this->_printer); // close the device we opened.
	libusb_exit(this->_context); // close the session.
}

void g2d::escpos::printer::initialize(std::pair<int, int> ids)
{
	g2d::basic::unused(ids);

	if (static_instance == nullptr)
	{
		static_instance = new g2d::escpos::printer();
	}
}

g2d::escpos::printer& g2d::escpos::printer::current()
{
	return *static_instance;
}

bool g2d::escpos::printer::text(std::string text)
{
    std::stack<g2d::escpos::data> formats;
    std::set<g2d::escpos::data> elements;
    std::string to_print;

	for (std::size_t counter = 0;; counter++)
	{
		try
		{
			if(counter == text.length()-1)
			{
				counter ++;

				exit(EXIT_FAILURE);
			}

			g2d::escpos::data mode = g2d::escpos::data::matching(text.substr(counter, 2));

			if (elements.find(mode) != elements.end() && formats.top() != mode )
			{
				std::cerr << "Incorrect text string with markdown" << std::endl;

				return false;
			}
			else if (elements.find(mode) == elements.end())
			{
				// first we add the characters of the string before this change.
				if (counter != 0)
				{
					to_print += text.substr(0, counter);
				}

				// we apply the effect.
				to_print += mode.first;
				elements.insert(mode);
				formats.push(mode);

				// we resize the string and are ready to continue;
				text = text.substr(counter + 2, text.length() - counter - 2);
				counter =-1;
			}
			else if (elements.find(mode) != elements.end() && formats.top() == mode)
			{
				// mode already inside, apply second sequence to string.
				if (counter != 0)
				{
					to_print += text.substr(0, counter);
				}

				to_print += mode.second;
				elements.erase(elements.find(mode));
				formats.pop();

				// we resize the string and are ready to continue;
				text = text.substr(counter + 2, text.length() - counter - 2);
				counter =-1;
			}
		}
		catch (int e)
		{
			// this means the text is still ok.
			if (counter == text.length())
			{
				if (!elements.empty())
				{
					std::clog << "Unmatched characters in markdown string" << std::endl;

					return false;
				}

				to_print += text;

				break;
			}
		}
	}

	this->raw(to_print);

	return true;
}

bool g2d::escpos::printer::cut(std::string text)
{
	if (g2d::escpos::printer::text(text))
	{
		this->cut();

		return true;
	}

	return false;
}

void g2d::escpos::printer::raw(std::string text)
{
	int totalChars = text.length();
	int actual = 0;
	int res = libusb_bulk_transfer(this->_printer, (1 | LIBUSB_ENDPOINT_OUT), (unsigned char *) &text[0], totalChars, &actual, 0);

	if (res != 0 || actual != totalChars)
	{
		std::clog << "Write Error" << std::endl;
	}
}

void g2d::escpos::printer::cut()
{
	this->raw(g2d::escpos::CUT);
}

void g2d::escpos::printer::reset()
{
	this->raw(g2d::escpos::RESET);
}
