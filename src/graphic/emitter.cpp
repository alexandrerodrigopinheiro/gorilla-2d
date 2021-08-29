#include "../../includes/graphic/emitter.h"

g2d::graphic::emitter::emitter()
	: _run(false)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _identity(0)
	, _atlas_index(0)
	, _allocated_particles(0)
	, _particle_size(0)
	, _total_particles(0)
	, _y_coord_flipped(1)
	, _blend_additive(true)
	, _auto_remove_on_finish(false)
	, _transform_emitter_dirty(false)
	, _active(true)
	, _opacity_modify_rgb(false)
	, _paused(false)
	, _start_position_compatible(false)
	, _gravity_rotation_is_directional(false)
	, _elapsed(0)
	, _emission_counter(0.0)
	, _duration(0.0)
	, _life(0.0)
	, _life_variance(0.0)
	, _angle(0.0)
	, _angle_variance(0.0)
	, _start_size(0.0)
	, _start_size_variance(0.0)
	, _end_size(0.0)
	, _end_size_variance(0.0)
	, _start_spin(0.0)
	, _start_spin_variance(0.0)
	, _end_spin(0.0)
	, _end_spin_variance(0.0)
	, _emission_rate(0.0)
	, _radius_start(0.0)
	, _radius_start_variance(0.0)
	, _radius_end(0.0)
	, _radius_end_variance(0.0)
	, _radius_rotate_per_second(0.0)
	, _radius_rotate_per_second_variance(0.0)
	, _filename(std::string())
	, _configuration_name(std::string())
	, _flip(g2d::graphic::flip::flip_none)
	, _mode(g2d::graphic::mode::mode_gravity)
	, _emission(g2d::graphic::emission::emission_none)
	, _pivot(g2d::math::point2dd(0.0))
	, _scale(g2d::math::size2dd(1.0))
	, _rotate(g2d::math::rotated())
	, _color(g2d::math::color(255))
	, _start_color(g2d::math::color(255))
	, _start_color_variance(g2d::math::color(255))
	, _end_color(g2d::math::color(255))
	, _end_color_variance(g2d::math::color(255))
	, _start_position(g2d::math::point3dd())
	, _position_variance(g2d::math::point3dd())
	, _position(g2d::math::point3dd())
	, _gravity_value(g2d::math::point3dd())
	, _gravity_speed(g2d::math::point3dd())
	, _gravity_speed_variance(g2d::math::point3dd())
	, _gravity_tangential_acceleration(g2d::math::point3dd())
	, _gravity_tangential_acceleration_variance(g2d::math::point3dd())
	, _gravity_radial_acceleration(g2d::math::point3dd())
	, _gravity_radial_acceleration_variance(g2d::math::point3dd())
	, _size(g2d::math::size2dd())
	, _vertex(g2d::math::vertexd(0.0))
	, _particles(std::vector<g2d::graphic::particle>())
{
}

g2d::graphic::emitter::~emitter()
{
	this->destroy();
}

bool g2d::graphic::emitter::initialize(const std::string& filename, const g2d::graphic::emission& emission, std::size_t amount, bool verbose)
{
	SDL_Surface* image = nullptr;

	image = IMG_Load(filename.c_str());

	if (image == nullptr)
	{
		std::cerr << "Cannot load texture '" << filename << "', failed." << std::endl;

		return false;
	}

	if (verbose)
	{
		std::clog << "Loading texture '" << filename << "', OK. -- " << image->format->BitsPerPixel << " bpp" << std::endl;
	}

	GLenum error = glGetError();

	glGenTextures(1, &this->_identity);
	glBindTexture(GL_TEXTURE_2D, this->_identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot generate texture: '" << gluErrorString(error) << "', failed" << std::endl;

		return false;
	}

	GLint internal_format = 0;
	GLint format = 0;

	switch (image->format->BytesPerPixel)
	{
		case 1:
		{
			internal_format = GL_LUMINANCE;
			format = GL_RED;
			break;
		}
		case 2:
		{
			internal_format = GL_LUMINANCE_ALPHA;
			format = GL_RG;
			break;
		}
		case 3:
		{
			internal_format = GL_RGB;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			format = GL_RGB;
#else
			format = GL_BGR;
#endif
			break;
		}
		case 4:
		{
			internal_format = GL_RGBA;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			format = GL_RGBA;
#else
			format = GL_BGRA;
#endif
			break;
		}
		default:
		{
			std::cerr << "Unknown image format, failed" << std::endl;

			exit(EXIT_FAILURE);
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, image->w % 4 == 0 ? 4 : 1);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	this->_source_size.set(static_cast<double>(image->w), static_cast<double>(image->h));
	this->_size.set(static_cast<double>(image->w), static_cast<double>(image->h));

	SDL_FreeSurface(image);

	this->_filename = filename;
	this->_verbose = verbose;
	this->_start_position.set(0.0);
	this->_total_particles = amount;
    this->_start_spin = 0.0;
    this->_start_spin_variance = 90.0;
    this->_end_spin = 90.0;
    this->_start_spin_variance = 90.0;

    this->bind();
    this->mapping();
    this->emission(emission);

	return true;
}

bool g2d::graphic::emitter::initialize(const g2d::graphic::texture& texture, const g2d::graphic::emission& emission, std::size_t amount, bool verbose)
{
	this->_identity = texture.identity();
	this->_size = texture.size();
	this->_filename = texture.filename();
	this->_verbose = verbose;
	this->_start_position.set(0.0);
	this->_total_particles = amount;
    this->_start_spin = 0.0;
    this->_start_spin_variance = 90.0;
    this->_end_spin = 90.0;
    this->_start_spin_variance = 90.0;
	this->_verbose = verbose;

    this->bind();
    this->mapping();
    this->emission(emission);

	return true;
}

void g2d::graphic::emitter::destroy()
{
	glDeleteTextures(1, &this->_identity);

	this->_particles.clear();
}

void g2d::graphic::emitter::draw()
{
	if (this->_visible && this->_scale != 0.0 && this->_color.a() != 0.0)
	{
		this->mapping();

		glPushMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND);

		glScaled(this->_scale.w(), this->_scale.h(), 1.0);

		glTranslated(
			this->_position.x(),
			this->_position.y(),
			this->_position.z()
		);

		glRotated(this->_rotate.h(), 1.0, 0.0, 0.0);
		glRotated(this->_rotate.p(), 0.0, 1.0, 0.0);
		glRotated(this->_rotate.b(), 0.0, 0.0, 1.0);

		glScaled(this->_scale.w(), this->_scale.h(), 1.0);

		glColor4d(
			this->_color.normal_r(),
			this->_color.normal_g(),
			this->_color.normal_b(),
			this->_color.normal_a()
		);

		for (std::size_t i = 0; i < this->_particle_size; i++)
		{
			if (this->_particles[i].size().w() <= 0.0 || this->_particles[i].size().h() <= 0.0 || this->_particles[i].color().a() <= 0.0)
			{
				std::cout << this->_particles[i].size() << std::endl;
				std::cout << this->_particles[i].color() << std::endl;
//				continue;
			}

			this->bind();

			this->_particles[i].flip(this->_flip);
			this->_particles[i].draw(this->_identity);
		}

		glDisable(GL_BLEND);
		glDisable(GL_COLOR_MATERIAL);

		if (this->_verbose)
		{
			glEnable(GL_LINE_STIPPLE);

			glTranslated(
				this->_start_position.x(),
				this->_start_position.y(),
				g2d::math::invert(this->_start_position.z())
			);

			glRotated(this->_rotate.h(), 1.0, 0.0, 0.0);
			glRotated(this->_rotate.p(), 0.0, 1.0, 0.0);
			glRotated(this->_rotate.b(), 0.0, 0.0, 1.0);

			glScaled(this->_scale.w(), this->_scale.h(), 1.0);

			glColor4d(0.0, 1.0, 0.0, 1.0);

			glLineWidth(2.0);
			glBegin(GL_LINE_LOOP);
			glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
			glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
			glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
			glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());
			glEnd();

			glColor4d(0.0, 0.0, 1.0, 1.0);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3d(-10.0, 0.0, 0.0);
			glVertex3d( 10.0, 0.0, 0.0);
			glEnd();

			glColor4d(1.0, 0.0, 0.0, 1.0);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3d(0.0, -10.0, 0.0);
			glVertex3d(0.0,  10.0, 0.0);
			glEnd();

			glDisable(GL_LINE_STIPPLE);
		}

		glPopMatrix();
	}
}

void g2d::graphic::emitter::update()
{
	double dt = 1.0 / 25;

	if (this->_active && this->_emission_rate > 0.0)
	{
		double rate = 1.0 / this->_emission_rate;
		std::size_t total_particles = this->_total_particles;

		if (this->_particle_size < total_particles)
		{
			this->_emission_counter += dt;

			if (this->_emission_counter < 0.0)
			{
				this->_emission_counter = 0.0;
			}
		}

		std::size_t emission_counter = (std::min)(1.0 * (total_particles - this->_particle_size), this->_emission_counter / rate);

		this->add_particles(emission_counter);

		this->_emission_counter -= rate * emission_counter;

		this->_elapsed += dt;

		if (this->_elapsed < 0.0)
		{
			this->_elapsed = 0.0;
		}

		if (this->_duration != g2d::graphic::DURATION_INFINITY && this->_duration < this->_elapsed)
		{
			this->stop_emitter();
		}
	}

	for (std::size_t i = 0; i < this->_particle_size; ++i)
	{
		this->_particles[i].append_time_to_live(-dt);
	}

	// rebirth.
	for (std::size_t i = 0; i < this->_particle_size; ++i)
	{
		if (this->_particles[i].time_to_live() <= 0.0)
		{
			//std::size_t j = this->_particle_size - 1;

			//while (j > 0 && this->_particles[i].time_to_live() <= 0)
			//{
			//	this->_particle_size--;
			//	j--;
			//}

			this->_particles[i] = this->_particles[this->_particle_size - 1];

			--this->_particle_size;
		}
	}

	if (this->_mode == g2d::graphic::mode::mode_gravity)
	{
		for (std::size_t i = 0; i < this->_particle_size; ++i)
		{
			g2d::math::point3dd tmp;
			g2d::math::point3dd tangential;
			g2d::math::point2dd radial;

			// radial acceleration
			if (this->_particles[i].position().x() || this->_particles[i].position().y())
			{
				radial = g2d::math::normalize_point2d(this->_particles[i].position().x(), this->_particles[i].position().y());
			}

			tangential.set(radial.x(), radial.y(), 0.0);

			radial.x(radial.x() * this->_particles[i].gravity_radial_acceleration());
			radial.y(radial.y() * this->_particles[i].gravity_radial_acceleration());

			// tangential acceleration.
			double tx = tangential.x();
			double ty = tangential.y();

			std::swap(tx, ty);

			tangential.x(tx);
			tangential.y(ty);

			tangential.x(tangential.x() * g2d::math::invert(this->_particles[i].gravity_tangential_acceleration()));
			tangential.y(tangential.y() * this->_particles[i].gravity_tangential_acceleration());

			// (gravity + radial + tangential) * dt.
			tmp.x(radial.x() + tangential.x() + this->_gravity_value.x());
			tmp.y(radial.y() + tangential.y() + this->_gravity_value.y());
			tmp.x(tmp.x() * dt);
			tmp.y(tmp.y() * dt);

			this->_particles[i].append_gravity_direction_x(tmp.x());
			this->_particles[i].append_gravity_direction_y(tmp.y());

			// this is cocos2d-x v3.0.
			tmp.x(this->_particles[i].gravity_direction().x() * dt * this->_y_coord_flipped);
			tmp.y(this->_particles[i].gravity_direction().y() * dt * this->_y_coord_flipped);

			this->_particles[i].append_position_x(tmp.x());
			this->_particles[i].append_position_y(tmp.y());
		}
	}
	else
	{
		for (std::size_t i = 0; i < this->_particle_size; ++i)
		{
			this->_particles[i].append_radius_angle(this->_particles[i].radius_degrees_per_second() * dt);
			this->_particles[i].append_radius_value(this->_particles[i].radius_delta_value() * dt);
			this->_particles[i].position_x(g2d::math::invert(std::cos(this->_particles[i].radius_angle()) * this->_particles[i].radius_value()));
			this->_particles[i].position_y(g2d::math::invert(std::sin(this->_particles[i].radius_angle()) * this->_particles[i].radius_value() * this->_y_coord_flipped));
		}
	}

	//color, size, rotation
	for (std::size_t i = 0; i < this->_particle_size; ++i)
	{
		this->_particles[i].append_color_r(this->_particles[i].delta_color().r() * dt);
		this->_particles[i].append_color_g(this->_particles[i].delta_color().g() * dt);
		this->_particles[i].append_color_b(this->_particles[i].delta_color().b() * dt);
		this->_particles[i].append_color_a(this->_particles[i].delta_color().a() * dt);
		this->_particles[i].append_size(this->_particles[i].delta_size().w() * dt);
		this->_particles[i].size(std::max(0.0, this->_particles[i].size().w()));
		this->_particles[i].append_rotate(this->_particles[i].delta_rotate().h() * dt);
	}
}

void g2d::graphic::emitter::resize_particles(std::size_t total_particles)
{
	if (this->_particles.size() < total_particles)
	{
		this->_particles.resize(total_particles);
	}

	for (std::size_t i = 0; i < total_particles; i++)
	{
		if (!this->_particles[i].initialize(this->_start_position, this->_source_size, this->_verbose))
		{
			std::cerr << "Cannot initialize particles, failed." << std::endl;

			exit(EXIT_FAILURE);
		}
	}
}

bool g2d::graphic::emitter::paused() const
{
	return this->_paused;
}

void g2d::graphic::emitter::pause()
{
	this->_paused = true;
}

void g2d::graphic::emitter::resume()
{
	this->_paused = false;
}

void g2d::graphic::emitter::add_particles(std::size_t amount)
{
	if (this->_paused)
	{
		return;
	}

	uint32_t rand_seed = rand();

	std::size_t start = this->_particle_size;
	this->_particle_size += amount;

	//life
	for (std::size_t i = start; i < this->_particle_size; ++i)
	{
		this->_particles[i].time_to_live(std::max(0.0, this->_life + this->_life_variance * g2d::math::random_m11(&rand_seed)));

		//position
		this->_particles[i].position_x(this->_start_position.x() + this->_position_variance.x() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].position_y(this->_start_position.y() + this->_position_variance.y() * g2d::math::random_m11(&rand_seed));

		this->_particles[i].color_r(this->_start_color.r() + this->_start_color_variance.r() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].color_g(this->_start_color.g() + this->_start_color_variance.g() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].color_b(this->_start_color.b() + this->_start_color_variance.b() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].color_a(this->_start_color.a() + this->_start_color_variance.a() * g2d::math::random_m11(&rand_seed));

		this->_particles[i].delta_color_r(this->_end_color.r() + this->_end_color_variance.r() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].delta_color_g(this->_end_color.g() + this->_end_color_variance.g() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].delta_color_b(this->_end_color.b() + this->_end_color_variance.b() * g2d::math::random_m11(&rand_seed));
		this->_particles[i].delta_color_a(this->_end_color.a() + this->_end_color_variance.a() * g2d::math::random_m11(&rand_seed));

		this->_particles[i].delta_color_r((this->_particles[i].delta_color().r() - this->_particles[i].color().r()) / this->_particles[i].time_to_live());
		this->_particles[i].delta_color_g((this->_particles[i].delta_color().g() - this->_particles[i].color().g()) / this->_particles[i].time_to_live());
		this->_particles[i].delta_color_b((this->_particles[i].delta_color().b() - this->_particles[i].color().b()) / this->_particles[i].time_to_live());
		this->_particles[i].delta_color_a((this->_particles[i].delta_color().a() - this->_particles[i].color().a()) / this->_particles[i].time_to_live());

		//size
		this->_particles[i].size(this->_start_size + this->_start_size_variance * g2d::math::random_m11(&rand_seed));
		this->_particles[i].size(std::max(0.0, this->_particles[i].size().h()));

		if (this->_end_size != g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE)
		{
			double end_size = std::max(0.0, (this->_end_size + this->_end_size_variance * g2d::math::random_m11(&rand_seed)));
			this->_particles[i].delta_size((end_size - this->_particles[i].size().h()) / this->_particles[i].time_to_live());
		}
		else
		{
			this->_particles[i].delta_size(0.0);
		}

		// rotation
//		this->_particles[i].rotate_h(this->_start_spin + this->_start_spin_variance * g2d::math::random_m11(&rand_seed));
//		this->_particles[i].rotate_p(this->_start_spin + this->_start_spin_variance * g2d::math::random_m11(&rand_seed));
		this->_particles[i].rotate_b(this->_start_spin + this->_start_spin_variance * g2d::math::random_m11(&rand_seed));

//		this->_particles[i].delta_rotate_h(((this->_end_spin + this->_end_spin_variance * g2d::math::random_m11(&rand_seed)) - this->_particles[i].rotate().h()) / this->_particles[i].time_to_live());
//		this->_particles[i].delta_rotate_p(((this->_end_spin + this->_end_spin_variance * g2d::math::random_m11(&rand_seed)) - this->_particles[i].rotate().p()) / this->_particles[i].time_to_live());
		this->_particles[i].delta_rotate_b(((this->_end_spin + this->_end_spin_variance * g2d::math::random_m11(&rand_seed)) - this->_particles[i].rotate().b()) / this->_particles[i].time_to_live());

		// position
		this->_particles[i].start_position_x(this->_start_position.x());
		this->_particles[i].start_position_y(this->_start_position.y());

		// g2d::graphic::mode gravity_value: A
		if (this->_mode == g2d::graphic::mode::mode_gravity)
		{
			// radial accel
			this->_particles[i].gravity_radial_acceleration(this->_gravity_radial_acceleration.x() + this->_gravity_radial_acceleration_variance.x() * g2d::math::random_m11(&rand_seed));
			this->_particles[i].gravity_tangential_acceleration(this->_gravity_tangential_acceleration.x() + this->_gravity_tangential_acceleration_variance.x() * g2d::math::random_m11(&rand_seed));

			// rotation is dir
			if (this->_gravity_rotation_is_directional)
			{
				double a = g2d::math::degrees_to_radians(this->_angle + this->_angle_variance * g2d::math::random_m11(&rand_seed));
				g2d::math::point3dd v(std::cos(a), std::sin(a), 0.0);
				double s = this->_gravity_speed.x() + this->_gravity_speed_variance.x() * g2d::math::random_m11(&rand_seed);
				g2d::math::point3dd direction = v * s;

				this->_particles[i].gravity_direction_x(direction.x());	//v * s ;
				this->_particles[i].gravity_direction_y(direction.y());
				this->_particles[i].rotate(g2d::math::invert(g2d::math::radians_to_degrees(direction.angle())));
			}
			else
			{
				double a = g2d::math::degrees_to_radians(this->_angle + this->_angle_variance * g2d::math::random_m11(&rand_seed));
				g2d::math::point3dd v(std::cos(a), std::sin(a), 0.0);
				double s = this->_gravity_speed.x() + this->_gravity_speed_variance.x() * g2d::math::random_m11(&rand_seed);
				g2d::math::point3dd direction = v * s;

				this->_particles[i].gravity_direction_x(direction.x());	//v * s ;
				this->_particles[i].gravity_direction_y(direction.y());
//				this->_particles[i].gravity_direction_z(direction.z());
			}
		}
		// g2d::graphic::mode Radius: B
		else
		{
			this->_particles[i].radius_value(this->_radius_start + this->_radius_start_variance * g2d::math::random_m11(&rand_seed));
			this->_particles[i].radius_value(g2d::math::degrees_to_radians(this->_angle + this->_angle_variance * g2d::math::random_m11(&rand_seed)));
			this->_particles[i].radius_degrees_per_second(g2d::math::degrees_to_radians(this->_radius_rotate_per_second + this->_radius_rotate_per_second_variance * g2d::math::random_m11(&rand_seed)));

			if (this->_radius_end == g2d::graphic::START_RADIUS_EQUAL_TO_END_RADIUS)
			{
				this->_particles[i].radius_delta_value(0.0);
			}
			else
			{
				double end_radius = this->_radius_end + this->_radius_end_variance * g2d::math::random_m11(&rand_seed);
				this->_particles[i].radius_delta_value((end_radius - this->_particles[i].radius_value()) / this->_particles[i].time_to_live());
			}
		}
	}
}

void g2d::graphic::emitter::stop_emitter()
{
	this->_active = false;
	this->_elapsed = this->_duration;
	this->_emission_counter = 0;
}

void g2d::graphic::emitter::reemitter()
{
	this->_active = true;
	this->_elapsed = 0;

	for (std::size_t i = 0; i < this->_particle_size; ++i)
	{
		 this->_particles[i].time_to_live(0.0);
	}
}

bool g2d::graphic::emitter::ended() const
{
	return (this->_particle_size == this->_total_particles);
}

bool g2d::graphic::emitter::auto_remove_on_finish() const
{
	return this->_auto_remove_on_finish;
}

void g2d::graphic::emitter::emission(const g2d::graphic::emission& emission)
{
	if (this->_emission == emission)
	{
		return;
	}

	this->_emission = emission;

	if (emission == g2d::graphic::emission::emission_none)
	{
		this->stop_emitter();
	}

	switch (emission)
	{
		case g2d::graphic::emission::emission_fire:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 250 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: radial acceleration
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-60);
			this->_gravity_speed_variance.set(20);

			// starting angle
			this->_angle = 90;
			this->_angle_variance = 10;

			// life of particles
			this->_life = 3;
			this->_life_variance = 0.25;

			// size, in pixels
			this->_start_size = 54.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per frame
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(193.8, 63.75, 30.6, 255.0);
			this->_start_color_variance.set(0.0);
			this->_end_color.set(0.0);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(40.0, 20.0, 0.0);

			break;
		}
		case g2d::graphic::emission::emission_firework:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 1500 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// Gravity Mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// Gravity Mode: gravity
			this->_gravity_value.set(0.0, 90.0, 0.0 );

			// Gravity Mode:  radial
			this->_gravity_radial_acceleration.set(0.0);
			this->_gravity_radial_acceleration_variance.set(0.0);

			//  Gravity Mode: speed of particles
			this->_gravity_speed.set(-180.0);
			this->_gravity_speed_variance.set(50.0);

			// angle
			this->_angle = 90.0;
			this->_angle_variance = 20.0;

			// life of particles
			this->_life = 3.5;
			this->_life_variance = 1.0;

			// emits per frame
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(127.5, 127.5, 127.5, 255.0);
			this->_start_color_variance.set(127.5, 127.5, 127.5, 25.5);
			this->_end_color.set(25.5, 25.5, 25.5, 51.0);
			this->_end_color_variance.set(25.5, 25.5, 25.5, 51.0);

			// size, in pixels
			this->_start_size = 8.0;
			this->_start_size_variance = 2.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_sun:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 350 : this->_total_particles);

			// additive
			//this->setBlendAdditive(true);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: radial acceleration
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-20);
			this->_gravity_speed_variance.set(5);

			// angle
			this->_angle = 90;
			this->_angle_variance = 360;

			// life of particles
			this->_life = 1;
			this->_life_variance = 0.5;

			// size, in pixels
			this->_start_size = 30.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per seconds
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(193.8, 63.75, 30.6, 255.0);
			this->_start_color_variance.set(0.0);
			this->_end_color.set(0.0, 0.0, 0.0, 25.5);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_galaxy:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 200 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-60);
			this->_gravity_speed_variance.set(10);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(-80);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(80);
			this->_gravity_tangential_acceleration_variance.set(0);

			// angle
			this->_angle = 90;
			this->_angle_variance = 360;

			// life of particles
			this->_life = 4;
			this->_life_variance = 1;

			// size, in pixels
			this->_start_size = 37.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(30.6, 63.75, 193.8, 255.0);
			this->_start_color_variance.set(0.0);
			this->_end_color.set(0.0, 0.0, 0.0, 25.5);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_flower:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 250 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-80);
			this->_gravity_speed_variance.set(10);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(-60);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(15);
			this->_gravity_tangential_acceleration_variance.set(0);

			// angle
			this->_angle = 90;
			this->_angle_variance = 360;

			// life of particles
			this->_life = 4;
			this->_life_variance = 1;

			// size, in pixels
			this->_start_size = 30.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(127.5, 127.5, 127.5, 255.0);
			this->_start_color_variance.set(127.5);
			this->_end_color.set(0.0, 0.0, 0.0, 25.5);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_meteor:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 150 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(-200.0, -200.0, 0.0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-15);
			this->_gravity_speed_variance.set(5);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(0);
			this->_gravity_tangential_acceleration_variance.set(0);

			// angle
			this->_angle = 90;
			this->_angle_variance = 360;

			// life of particles
			this->_life = 2;
			this->_life_variance = 1;

			// size, in pixels
			this->_start_size = 60.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(51.0, 102.0, 178.5, 255.0);
			this->_start_color_variance.set(0.0, 0.0, 51.0, 25.5);
			this->_end_color.set(0.0, 0.0, 0.0, 25.5);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_spiral:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 500 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-150);
			this->_gravity_speed_variance.set(0);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(-380);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(45);
			this->_gravity_tangential_acceleration_variance.set(0);

			// angle
			this->_angle = 90;
			this->_angle_variance = 0;

			// life of particles
			this->_life = 12;
			this->_life_variance = 0;

			// size, in pixels
			this->_start_size = 20.0;
			this->_start_size_variance = 0.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(127.5, 127.5, 127.5, 255.0);
			this->_start_color_variance.set(127.5, 127.5, 127.5, 0.0);
			this->_end_color.set(127.5, 127.5, 127.5, 255.0);
			this->_end_color_variance.set(127.5, 127.5, 127.5, 0.0);

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_explosion:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 700 : this->_total_particles);

			// duration
			this->_duration = 0.1f;

			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-70);
			this->_gravity_speed_variance.set(40);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(0);
			this->_gravity_tangential_acceleration_variance.set(0);

			// angle
			this->_angle = 90;
			this->_angle_variance = 360;

			// life of particles
			this->_life = 5.0;
			this->_life_variance = 2;

			// size, in pixels
			this->_start_size = 15.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = this->_total_particles / this->_duration;

			// color of particles
			this->_start_color.set(178.5, 25.5, 51.0, 255.0);
			this->_start_color_variance.set(127.5, 127.5, 127.5, 0.0);
			this->_end_color.set(127.5, 127.5, 127.5, 0.0);
			this->_end_color_variance.set(127.5, 127.5, 127.5, 0.0);

			this->_position_variance.set(0.0);

			break;
		}
		case g2d::graphic::emission::emission_smoke:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 200 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// graphic mode: gravity mode
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0);

			// gravity mode: radial acceleration
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-25);
			this->_gravity_speed_variance.set(10);

			// angle
			this->_angle = 90;
			this->_angle_variance = 5;

			// life of particles
			this->_life = 4;
			this->_life_variance = 1;

			// size, in pixels
			this->_start_size = 60.0;
			this->_start_size_variance = 10.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per frame
			this->_emission_rate = this->_total_particles / this->_life;

			// color of particles
			this->_start_color.set(204.0, 204.0, 204.0, 255.0);
			this->_start_color_variance.set(5.1, 5.1, 5.1, 0.0);
			this->_end_color.set(0.0, 0.0, 0.0, 255.0);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(20.0, 0.0, 0.0);

			break;
		}
		case g2d::graphic::emission::emission_snow:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 700 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			// this-> gravity mode.
			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(0.0, 1.0, 0.0);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-5);
			this->_gravity_speed_variance.set(1);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(1);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(0);
			this->_gravity_tangential_acceleration_variance.set(1);

			// angle
			this->_angle = -90;
			this->_angle_variance = 5;

			// life of particles
			this->_life = 45;
			this->_life_variance = 15;

			// size, in pixels
			this->_start_size = 10.0;
			this->_start_size_variance = 5.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = 10;

			// color of particles
			this->_start_color.set(255.0);
			this->_start_color_variance.set(0.0);
			this->_end_color.set(25.5, 25.5, 25.5, 255.0);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(1.0 * this->_position.x(), 0.0, 0.0);

			break;
		}
		case g2d::graphic::emission::emission_rain:
		{
			this->initialize_with_total_particles(this->_total_particles == 0 ? 1000 : this->_total_particles);

			// duration
			this->_duration = g2d::graphic::DURATION_INFINITY;

			this->_mode = g2d::graphic::mode::mode_gravity;

			// gravity mode: gravity
			this->_gravity_value.set(10.0, 10.0, 0.0);

			// gravity mode: radial
			this->_gravity_radial_acceleration.set(0);
			this->_gravity_radial_acceleration_variance.set(1);

			// gravity mode: tangential
			this->_gravity_tangential_acceleration.set(0);
			this->_gravity_tangential_acceleration_variance.set(1);

			// gravity mode: speed of particles
			this->_gravity_speed.set(-130);
			this->_gravity_speed_variance.set(30);

			// angle
			this->_angle = -90;
			this->_angle_variance = 5;

			// life of particles
			this->_life = 4.5;
			this->_life_variance = 0;

			// size, in pixels
			this->_start_size = 4.0;
			this->_start_size_variance = 2.0;
			this->_end_size = g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE;

			// emits per second
			this->_emission_rate = 20;

			// color of particles
			this->_start_color.set(178.5, 204.0, 255.0, 255.0);
			this->_start_color_variance.set(0.0);
			this->_end_color.set(178.5, 204.0, 255.0, 127.5);
			this->_end_color_variance.set(0.0);

			this->_position_variance.set(1.0 * this->_position.x(), 0.0, 0.0);

			break;
		}
		default:
		{
			break;
		}
	}
}

void g2d::graphic::emitter::auto_remove_on_finish(bool auto_remove_on_finish)
{
	this->_auto_remove_on_finish = auto_remove_on_finish;
}

void g2d::graphic::emitter::gravity_value(const g2d::math::point3dd& gravity_value)
{
	this->_gravity_value = gravity_value;
}

void g2d::graphic::emitter::gravity_speed(double gravity_speed)
{
	this->_gravity_speed = gravity_speed;
}

void g2d::graphic::emitter::gravity_speed_variance(double gravity_speed_variance)
{
	this->_gravity_speed_variance = gravity_speed_variance;
}

void g2d::graphic::emitter::gravity_tangential_acceleration(double gravity_tangential_acceleration)
{
	this->_gravity_tangential_acceleration = gravity_tangential_acceleration;
}

void g2d::graphic::emitter::gravity_tangential_acceleration_variance(double gravity_tangential_acceleration_variance)
{
	this->_gravity_tangential_acceleration_variance = gravity_tangential_acceleration_variance;
}

void g2d::graphic::emitter::gravity_radial_acceleration(double gravity_radial_acceleration)
{
	this->_gravity_radial_acceleration = gravity_radial_acceleration;
}

void g2d::graphic::emitter::gravity_radial_acceleration_variance(double gravity_radial_acceleration_variance)
{
	this->_gravity_radial_acceleration_variance = gravity_radial_acceleration_variance;
}

void g2d::graphic::emitter::gravity_rotation_is_directional(bool gravity_rotation_is_directional)
{
	this->_gravity_rotation_is_directional = gravity_rotation_is_directional;
}

void g2d::graphic::emitter::radius_start(double radius_start)
{
	this->_radius_start = radius_start;
}

void g2d::graphic::emitter::radius_start_variance(double radius_start_variance)
{
	this->_radius_start_variance = radius_start_variance;
}

void g2d::graphic::emitter::end_radius(double end_radius)
{
	this->_radius_end = end_radius;
}

void g2d::graphic::emitter::end_radius_variance(double end_radius_variance)
{
	this->_radius_end_variance = end_radius_variance;
}

void g2d::graphic::emitter::radius_rotate_per_second(double degrees)
{
	this->_radius_rotate_per_second = degrees;
}

void g2d::graphic::emitter::radius_rotate_per_second_variance(double degrees)
{
	this->_radius_rotate_per_second_variance = degrees;
}

void g2d::graphic::emitter::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::emitter::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::emitter::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::emitter::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::emitter::atlas_index(std::size_t index)
{
	this->_atlas_index = index;
}

void g2d::graphic::emitter::duration(double duration)
{
	this->_duration = duration;
}

void g2d::graphic::emitter::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::emitter::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::emitter::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::emitter::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::emitter::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::emitter::position(double x, double y, double z)
{
	this->_position.set(x, y, z);
}

void g2d::graphic::emitter::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::emitter::position(double position)
{
	this->_position = position;
}

void g2d::graphic::emitter::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::emitter::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::emitter::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::emitter::position_variance(const g2d::math::point3dd& position)
{
	this->_position_variance = position;
}

void g2d::graphic::emitter::life(double life)
{
	this->_life = life;
}

void g2d::graphic::emitter::life_variance(double life_variance)
{
	this->_life_variance = life_variance;
}

void g2d::graphic::emitter::angle(double angle)
{
	this->_angle = angle;
}

void g2d::graphic::emitter::angle_variance(double angle_variance)
{
	this->_angle_variance = angle_variance;
}

void g2d::graphic::emitter::flip(const g2d::graphic::flip& flip)
{
	this->_flip = flip;
}

void g2d::graphic::emitter::mode(const g2d::graphic::mode& mode)
{
	this->_mode = mode;
}

void g2d::graphic::emitter::start_size(double start_size)
{
	this->_start_size = start_size;
}

void g2d::graphic::emitter::start_size_variance(double start_size_variance)
{
	this->_start_size_variance = start_size_variance;
}

void g2d::graphic::emitter::end_size(double end_size)
{
	this->_end_size = end_size;
}

void g2d::graphic::emitter::end_size_variance(double end_size_variance)
{
	this->_end_size_variance = end_size_variance;
}

void g2d::graphic::emitter::size(const g2d::math::size2dd& size)
{
	this->_size = size;
}

void g2d::graphic::emitter::size(double w, double h)
{
	this->_size.set(w, h);
}

void g2d::graphic::emitter::size(double size)
{
	this->_size = size;
}

void g2d::graphic::emitter::size_w(double w)
{
	this->_size.w(w);
}

void g2d::graphic::emitter::size_h(double h)
{
	this->_size.h(h);
}

void g2d::graphic::emitter::start_color(const g2d::math::color& start_color)
{
	this->_start_color = start_color;
}

void g2d::graphic::emitter::start_color_variance(const g2d::math::color& start_color_variance)
{
	this->_start_color_variance = start_color_variance;
}

void g2d::graphic::emitter::end_color(const g2d::math::color& end_color)
{
	this->_end_color = end_color;
}

void g2d::graphic::emitter::end_color_variance(const g2d::math::color& end_color_variance)
{
	this->_end_color_variance = end_color_variance;
}

void g2d::graphic::emitter::start_spin(double start_spin)
{
	this->_start_spin = start_spin;
}

void g2d::graphic::emitter::start_spin_variance(double start_spin_variance)
{
	this->_start_spin_variance = start_spin_variance;
}

void g2d::graphic::emitter::end_spin(double end_spin)
{
	this->_end_spin = end_spin;
}

void g2d::graphic::emitter::end_spin_variance(double end_spin_variance)
{
	this->_end_spin_variance = end_spin_variance;
}

void g2d::graphic::emitter::emission_rate(double emission_rate)
{
	this->_emission_rate = emission_rate;
}

void g2d::graphic::emitter::total_particles(std::size_t total_particles)
{
	this->_total_particles = total_particles;
}

void g2d::graphic::emitter::opacity_modify_rgb(bool opacity_modify_rgb)
{
	this->_opacity_modify_rgb = opacity_modify_rgb;
}

const g2d::math::point3dd& g2d::graphic::emitter::gravity_value()
{
	return this->_gravity_value;
}

const g2d::math::point3dd& g2d::graphic::emitter::gravity_speed() const
{
	return this->_gravity_speed;
}

const g2d::math::point3dd& g2d::graphic::emitter::speed_variance() const
{
	return this->_gravity_speed_variance;
}

const g2d::math::point3dd& g2d::graphic::emitter::gravity_tangential_acceleration() const
{
	return this->_gravity_tangential_acceleration;
}

const g2d::math::point3dd& g2d::graphic::emitter::gravity_tangential_acceleration_variance() const
{
	return this->_gravity_tangential_acceleration_variance;
}

const g2d::math::point3dd& g2d::graphic::emitter::radial_acceleration() const
{
	return this->_gravity_radial_acceleration;
}

const g2d::math::point3dd& g2d::graphic::emitter::gravity_radial_acceleration_variance() const
{
	return this->_gravity_radial_acceleration_variance;
}

bool g2d::graphic::emitter::gravity_rotation_is_directional() const
{
	return this->_gravity_rotation_is_directional;
}

double g2d::graphic::emitter::radius_start() const
{
	return this->_radius_start;
}

double g2d::graphic::emitter::radius_start_variance() const
{
	return this->_radius_start_variance;
}

double g2d::graphic::emitter::end_radius() const
{
	return this->_radius_end;
}

double g2d::graphic::emitter::end_radius_variance() const
{
	return this->_radius_end_variance;
}

double g2d::graphic::emitter::radius_rotate_per_second() const
{
	return this->_radius_rotate_per_second;
}

double g2d::graphic::emitter::radius_rotate_per_second_variance() const
{
	return this->_radius_rotate_per_second_variance;
}

bool g2d::graphic::emitter::active() const
{
	return this->_active;
}

std::size_t g2d::graphic::emitter::atlas_index() const
{
	return this->_atlas_index;
}

std::size_t g2d::graphic::emitter::particle_count() const
{
	return this->_particle_size;
}

double g2d::graphic::emitter::duration() const
{
	return this->_duration;
}

const g2d::math::point3dd& g2d::graphic::emitter::position() const
{
	return this->_position;
}

const g2d::math::point3dd& g2d::graphic::emitter::position_variance() const
{
	return this->_position_variance;
}

double g2d::graphic::emitter::life() const
{
	return this->_life;
}

double g2d::graphic::emitter::life_variance() const
{
	return this->_life_variance;
}

double g2d::graphic::emitter::angle() const
{
	return this->_angle;
}

double g2d::graphic::emitter::angle_variance() const
{
	return this->_angle_variance;
}

const g2d::graphic::flip& g2d::graphic::emitter::flip() const
{
	return this->_flip;
}

const g2d::graphic::mode& g2d::graphic::emitter::mode() const
{
	return this->_mode;
}

double g2d::graphic::emitter::start_size() const
{
	return this->_start_size;
}

double g2d::graphic::emitter::start_size_variance() const
{
	return this->_start_size_variance;
}

double g2d::graphic::emitter::end_size() const
{
	return this->_end_size;
}

double g2d::graphic::emitter::end_size_variance() const
{
	return this->_end_size_variance;
}

const g2d::math::color& g2d::graphic::emitter::start_color() const
{
	return this->_start_color;
}

const g2d::math::color& g2d::graphic::emitter::start_color_variance() const
{
	return this->_start_color_variance;
}

const g2d::math::color& g2d::graphic::emitter::end_color() const
{
	return this->_end_color;
}

const g2d::math::color& g2d::graphic::emitter::end_color_variance() const
{
	return this->_end_color_variance;
}

double g2d::graphic::emitter::start_spin() const
{
	return this->_start_spin;
}

double g2d::graphic::emitter::start_spin_variance() const
{
	return this->_start_spin_variance;
}

double g2d::graphic::emitter::end_spin() const
{
	return this->_end_spin;
}

double g2d::graphic::emitter::end_spin_variance() const
{
	return this->_end_spin_variance;
}

double g2d::graphic::emitter::emission_rate() const
{
	return this->_emission_rate;
}

std::size_t g2d::graphic::emitter::total_particles() const
{
	return this->_total_particles;
}

bool g2d::graphic::emitter::opacity_modify_rgb() const
{
	return this->_opacity_modify_rgb;
}

bool g2d::graphic::emitter::initialize_with_total_particles(std::size_t total_particles)
{
	this->_total_particles = total_particles;
	this->_active = true;
	this->_mode = g2d::graphic::mode::mode_gravity;
	this->_auto_remove_on_finish = false;
	this->_transform_emitter_dirty = false;

	this->resize_particles(total_particles);

	return true;
}

void g2d::graphic::emitter::bind(const g2d::graphic::filter& filter, const g2d::graphic::wrap& wrap)
{
	GLenum error = glGetError();

	glBindTexture(GL_TEXTURE_2D, this->_identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;

		exit(EXIT_FAILURE);
	}

	switch (filter)
	{
		default:
		{
			break;
		}
		case g2d::graphic::filter::filter_nearest:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			break;
		}
		case g2d::graphic::filter::filter_linear:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			break;
		}
	}

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot filter identity: '" << gluErrorString(error) << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	switch (wrap)
	{
		default:
		{
			break;
		}
		case g2d::graphic::wrap::wrap_nearest:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

			break;
		}
		case g2d::graphic::wrap::wrap_clamp:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			break;
		}
	}

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot wrap identity: '" << gluErrorString(error) << "', failed" << std::endl;

		return;
	}
}

void g2d::graphic::emitter::mapping()
{
	double x = g2d::math::invert(this->_size.w() * this->_pivot.x());
	double y = g2d::math::invert(this->_size.h() * this->_pivot.y());
	double w = x + this->_size.w();
	double h = y + this->_size.h();

	this->_vertex.a(x, y, 0.0);
	this->_vertex.b(w, y, 0.0);
	this->_vertex.c(w, h, 0.0);
	this->_vertex.d(x, h, 0.0);
}
