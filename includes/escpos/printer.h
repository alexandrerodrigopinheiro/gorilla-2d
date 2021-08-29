#ifndef G2D_ESCPOS_PRINTER_H_
#define G2D_ESCPOS_PRINTER_H_

#pragma once

#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <set>

#include <libusb-1.0/libusb.h>

#include "../basic/basic.h"

#include "printer.h"
#include "data.h"
#include "escpos.h"

namespace g2d
{
	namespace escpos
	{
		class printer
		{
			public:

				static void initialize(std::pair<int, int> ids);

			    static g2d::escpos::printer& current();

			    // output functions
			    //! otputs semi-markdown text to printer.
			    bool text(std::string text);

			    //! outputs semi-markdown text to printer cutting in the end.
			    bool cut(std::string text);

			    //! sends raw char stream to printer.
			    void raw(std::string text);

			    //! cuts the paper (by default, leaves some space).
			    void cut();

			    //! underline text.
			    void underline(bool state);

			    //! set defaults for printing.
			    void reset();

			private:

			    printer();

			    ~printer();

			    static g2d::escpos::printer* static_instance;
			    libusb_context* _context { nullptr };
			    libusb_device_handle* _printer { nullptr };
		};
	}
}

#endif /* G2D_ESCPOS_PRINTER_H_ */
