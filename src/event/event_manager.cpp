#include "../../includes/event/event_manager.h"

g2d::event::event_manager::event_manager()
	: _released(false)
	, _pressed(false)
	, _open(true)
	, _verbose(false)
	, _type(g2d::event::type::type_none)
	, _keyoard(g2d::event::keyboard())
	, _mouse(g2d::event::mouse())
	, _touch(g2d::event::touch())
	, _touch_pulse(nullptr)
{
}

g2d::event::event_manager::~event_manager()
{
	this->destroy();
}

bool g2d::event::event_manager::initialize(bool verbose)
{
	this->_verbose = verbose;
	this->_touch_pulse = new g2d::graphic::sprite();

	if (!SDL_WasInit(SDL_INIT_EVENTS))
	{
		SDL_Init(SDL_INIT_EVENTS);
	}

	if (!SDL_WasInit(SDL_INIT_EVENTS))
	{
		std::cerr << "Could not initializing keyboard, failed" << std::endl;

		return false;
	}

	if (!this->_touch_pulse->initialize("./assets/extra/pulse.png", 5, 1, 5, this->_verbose))
	{
		std::cerr << "Could not initializing touch pulse, failed." << std::endl;

		return false;
	}

	this->_touch_pulse->pivot(0.5);

	if (!this->_touch_pulse->animation("TOUCH_PULSE", 4))
	{
		std::cerr << "Could not initializing touch pulse animation, failed." << std::endl;

		return false;
	}

	this->_touch_pulse->visible(false);
	this->_touch_pulse->animation()->bind_index(0, 0);
	this->_touch_pulse->animation()->bind_index(4, 4);
	this->_touch_pulse->animation()->control(g2d::animation::control::control_cycle);
	this->_touch_pulse->pause();

	return true;
}

void g2d::event::event_manager::destroy()
{
	delete this->_touch_pulse;
	this->_touch_pulse = nullptr;
}

void g2d::event::event_manager::listener()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
			{
				this->_open = false;
				break;
			}
			case SDL_KEYUP:
			{
				this->_keyoard.released_key(g2d::event::key::key_released);
				this->_released = true;

				switch (event.key.keysym.sym)
				{
					case SDLK_p:
					{
						this->_keyoard.released_button(g2d::event::button::button_play);
						break;
					}
					case SDLK_t:
					{
						this->_keyoard.released_button(g2d::event::button::button_turbo);
						break;
					}
					case SDLK_o:
					{
						this->_keyoard.released_button(g2d::event::button::button_autoplay);
						break;
					}
					case SDLK_i:
					{
						this->_keyoard.released_button(g2d::event::button::button_extraball);
						break;
					}
					case SDLK_q:
					{
						this->_keyoard.released_button(g2d::event::button::button_decrease_speed);
						break;
					}
					case SDLK_w:
					{
						this->_keyoard.released_button(g2d::event::button::button_increase_speed);
						break;
					}
					case SDLK_e:
					{
						this->_keyoard.released_button(g2d::event::button::button_change_pattern);
						break;
					}
					case SDLK_a:
					{
						this->_keyoard.released_button(g2d::event::button::button_maximum_pattern);
						break;
					}
					case SDLK_s:
					{
						this->_keyoard.released_button(g2d::event::button::button_decrease_pattern);
						break;
					}
					case SDLK_d:
					{
						this->_keyoard.released_button(g2d::event::button::button_increase_pattern);
						break;
					}
					case SDLK_z:
					{
						this->_keyoard.released_button(g2d::event::button::button_maximum_bet);
						break;
					}
					case SDLK_x:
					{
						this->_keyoard.released_button(g2d::event::button::button_decrease_bet);
						break;
					}
					case SDLK_c:
					{
						this->_keyoard.released_button(g2d::event::button::button_increase_bet);
						break;
					}
					case SDLK_j:
					{
						this->_keyoard.released_button(g2d::event::button::button_credit);
						break;
					}
					case SDLK_k:
					{
						this->_keyoard.released_button(g2d::event::button::button_setting);
						break;
					}
					case SDLK_l:
					{
						this->_keyoard.released_button(g2d::event::button::button_cashout);
						break;
					}
					case SDLK_y:
					{
						this->_keyoard.released_button(g2d::event::button::button_payment);
						break;
					}
					case SDLK_n:
					{
						this->_keyoard.released_button(g2d::event::button::button_log);
						break;
					}
					case SDLK_m:
					{
						this->_keyoard.released_button(g2d::event::button::button_help);
						break;
					}
					case SDLK_r:
					{
						this->_keyoard.released_button(g2d::event::button::button_read);
						break;
					}
					case SDLK_1:
					{
						this->_keyoard.released_button(g2d::event::button::button_debug_fullscreen);
						break;
					}
					case SDLK_2:
					{
						this->_keyoard.released_button(g2d::event::button::button_debug_info);
						break;
					}
					case SDLK_3:
					{
						this->_keyoard.released_button(g2d::event::button::button_debug_ruler);
						break;
					}
					default:
					{
						this->_keyoard.released_button(g2d::event::button::button_invalid);
						break;
					}
				}

				break;
			}
			case SDL_KEYDOWN:
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					this->_open = false;
				}

				this->_keyoard.pressed_key(g2d::event::key::key_pressed);
				this->_pressed = true;

				switch (event.key.keysym.sym)
				{
					case SDLK_p:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_play);
						break;
					}
					case SDLK_t:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_turbo);
						break;
					}
					case SDLK_o:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_autoplay);
						break;
					}
					case SDLK_i:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_extraball);
						break;
					}
					case SDLK_q:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_decrease_speed);
						break;
					}
					case SDLK_w:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_increase_speed);
						break;
					}
					case SDLK_e:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_change_pattern);
						break;
					}
					case SDLK_a:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_maximum_pattern);
						break;
					}
					case SDLK_s:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_decrease_pattern);
						break;
					}
					case SDLK_d:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_increase_pattern);
						break;
					}
					case SDLK_z:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_maximum_bet);
						break;
					}
					case SDLK_x:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_decrease_bet);
						break;
					}
					case SDLK_c:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_increase_bet);
						break;
					}
					case SDLK_j:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_credit);
						break;
					}
					case SDLK_k:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_setting);
						break;
					}
					case SDLK_l:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_cashout);
						break;
					}
					case SDLK_y:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_payment);
						break;
					}
					case SDLK_n:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_log);
						break;
					}
					case SDLK_m:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_help);
						break;
					}
					case SDLK_r:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_read);
						break;
					}
					case SDLK_1:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_debug_fullscreen);
						break;
					}
					case SDLK_2:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_debug_info);
						break;
					}
					case SDLK_3:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_debug_ruler);
						break;
					}
					default:
					{
						this->_keyoard.pressed_button(g2d::event::button::button_invalid);
						break;
					}
				}

				break;
			}
			case SDL_MOUSEMOTION:
			{
				this->_mouse.cursor(g2d::event::cursor::cursor_motion);
				this->_mouse.position(event.motion.x, event.motion.y);

				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				this->_mouse.cursor(g2d::event::cursor::cursor_released);
				this->_mouse.position(event.motion.x, event.motion.y);
				this->_touch_pulse->pause();
				this->_touch_pulse->visible(false);

				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				this->_pressed = true;
				this->_mouse.cursor(g2d::event::cursor::cursor_pressed);
				this->_mouse.position(event.motion.x, event.motion.y);
				this->_touch_pulse->position(event.motion.x, event.motion.y, 0.0);
				this->_touch_pulse->replay();
				this->_touch_pulse->visible(true);

				break;
			}
			case SDL_FINGERMOTION:
			{
				this->_touch.finger(g2d::event::finger::finger_motion);
				this->_touch.position(event.tfinger.x, event.tfinger.y);
				this->_touch_pulse->position(event.tfinger.x, event.tfinger.y, 0.0);

				break;
			}
			case SDL_FINGERUP:
			{
				this->_touch.finger(g2d::event::finger::finger_released);
				this->_touch.position(event.tfinger.x, event.tfinger.y);
				this->_touch_pulse->pause();
				this->_touch_pulse->visible(false);

				break;
			}
			case SDL_FINGERDOWN:
			{
				this->_pressed = true;
				this->_touch.finger(g2d::event::finger::finger_pressed);
				this->_touch.position(event.tfinger.x, event.tfinger.y);
				this->_touch_pulse->position(event.tfinger.x, event.tfinger.y, 0.0);
				this->_touch_pulse->replay();
				this->_touch_pulse->visible(true);

				break;
			}
			default: break;
		}
	}

	if ((this->_pressed && this->_verbose) || (this->_released && this->_verbose))
	{
		switch (this->_keyoard.released_button())
		{
			case g2d::event::button::button_play:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_turbo:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_autoplay:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_extraball:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_decrease_speed:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_increase_speed:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_change_pattern:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_maximum_pattern:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_decrease_pattern:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_increase_pattern:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_maximum_bet:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_decrease_bet:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_increase_bet:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_credit:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_setting:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_payment:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_cashout:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_log:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_help:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_read:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_debug_fullscreen:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_debug_info:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			case g2d::event::button::button_debug_ruler:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
			default:
			{
				std::cout << this->_keyoard.released_button() << std::endl;
				break;
			}
		}

		switch (this->_keyoard.pressed_button())
		{
			case g2d::event::button::button_play:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_turbo:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_autoplay:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_extraball:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_decrease_speed:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_increase_speed:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_change_pattern:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_maximum_pattern:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_decrease_pattern:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_increase_pattern:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_maximum_bet:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_decrease_bet:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_increase_bet:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_credit:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_setting:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_payment:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_cashout:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_log:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_help:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_read:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_debug_fullscreen:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_debug_info:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			case g2d::event::button::button_debug_ruler:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
			default:
			{
				std::cout << this->_keyoard.pressed_button() << std::endl;
				break;
			}
		}

		switch (this->_mouse.cursor())
		{
			case g2d::event::cursor::cursor_motion:
			{
				std::cout << this->_mouse.cursor() << std::endl;
				break;
			}
			case g2d::event::cursor::cursor_released:
			{
				std::cout << this->_mouse.cursor() << std::endl;
				break;
			}
			case g2d::event::cursor::cursor_pressed:
			{
				std::cout << this->_mouse.cursor() << std::endl;
				break;
			}
			default:
			{
				break;
			}
		}

		switch (this->_touch.finger())
		{
			case g2d::event::finger::finger_motion:
			{
				std::cout << this->_touch.finger() << std::endl;
				break;
			}
			case g2d::event::finger::finger_released:
			{
				std::cout << this->_touch.finger() << std::endl;
				break;
			}
			case g2d::event::finger::finger_pressed:
			{
				std::cout << this->_touch.finger() << std::endl;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void g2d::event::event_manager::render()
{
	this->_touch_pulse->draw();
	this->_touch_pulse->run();
}

void g2d::event::event_manager::release()
{
	this->_type = g2d::event::type::type_none;
	this->_keyoard.clear();
	this->_mouse.clear();
	this->_touch.clear();
	this->_pressed = false;
	this->_released = false;
}

const g2d::event::keyboard& g2d::event::event_manager::keyoard() const
{
	return this->_keyoard;
}

const g2d::event::mouse& g2d::event::event_manager::mouse() const
{
	return this->_mouse;
}

const g2d::event::touch& g2d::event::event_manager::touch() const
{
	return this->_touch;
}

void g2d::event::event_manager::verbose(bool verbose)
{
	this->_verbose = verbose;
}

bool g2d::event::event_manager::opened() const
{
	return this->_open;
}

bool g2d::event::event_manager::verbosed() const
{
	return this->_verbose;
}
