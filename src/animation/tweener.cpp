#include "../../includes/animation/tweener.h"

g2d::animation::tweener::tweener()
	: _identity(std::string())
	, _timeline(nullptr)
	, _measure(std::vector<g2d::animation::keyframe<std::size_t>>())
	, _content(std::vector<g2d::animation::keyframe<std::string>>())
	, _hinting(std::vector<g2d::animation::keyframe<g2d::graphic::hinting>>())
	, _weight(std::vector<g2d::animation::keyframe<g2d::graphic::weight>>())
	, _dots(std::vector<g2d::animation::keyframe<std::size_t>>())
	, _index(std::vector<g2d::animation::keyframe<std::size_t>>())
	, _visible(std::vector<g2d::animation::keyframe<bool>>())
	, _wireframe(std::vector<g2d::animation::keyframe<bool>>())
	, _form(std::vector<g2d::animation::keyframe<g2d::graphic::form>>())
	, _flip(std::vector<g2d::animation::keyframe<g2d::graphic::flip>>())
	, _color(std::vector<g2d::animation::keyframe<g2d::math::color>>())
	, _pivot(std::vector<g2d::animation::keyframe<g2d::math::point2dd>>())
	, _position(std::vector<g2d::animation::keyframe<g2d::math::point3dd>>())
	, _scale(std::vector<g2d::animation::keyframe<g2d::math::size2dd>>())
	, _rotate(std::vector<g2d::animation::keyframe<g2d::math::rotated>>())
	, _size(std::vector<g2d::animation::keyframe<g2d::math::size2dd>>())
{
}

g2d::animation::tweener::~tweener()
{
	this->destroy();
}

bool g2d::animation::tweener::initialize(const std::string& identity, std::size_t length, std::size_t fps)
{
	this->_timeline = new g2d::animation::timeline();

	if (!this->_timeline->initialize(length, fps))
	{
		return false;
	}

	this->_timeline->stop();

	this->_identity = identity;

	return true;
}

void g2d::animation::tweener::destroy()
{
	delete this->_timeline;

	this->_timeline = nullptr;

	this->clear();
}

void g2d::animation::tweener::run()
{
	this->_timeline->run();
}

void g2d::animation::tweener::play()
{
	this->_timeline->play();
}

void g2d::animation::tweener::stop()
{
	this->_timeline->stop();
}

void g2d::animation::tweener::replay()
{
	this->_timeline->replay();
}

void g2d::animation::tweener::reset()
{
	this->_timeline->reset();
}

bool g2d::animation::tweener::played() const
{
	return this->_timeline->played();
}

bool g2d::animation::tweener::bound() const
{
	return this->_timeline->bound();
}

bool g2d::animation::tweener::onset() const
{
	return this->_timeline->onset();
}

std::size_t g2d::animation::tweener::length() const
{
	return this->_timeline->length();
}

std::size_t g2d::animation::tweener::frame() const
{
	return this->_timeline->frame();
}

void g2d::animation::tweener::course(const g2d::animation::course& course)
{
	this->_timeline->course(course);
}

void g2d::animation::tweener::control(const g2d::animation::control& control)
{
	this->_timeline->control(control);
}

const g2d::animation::course& g2d::animation::tweener::course() const
{
	return this->_timeline->course();
}

const g2d::animation::control& g2d::animation::tweener::control() const
{
	return this->_timeline->control();
}

void g2d::animation::tweener::bind_measure(std::size_t keyframe, std::size_t measure)
{
	this->_measure.push_back(g2d::animation::keyframe<std::size_t>(keyframe, measure));
}

void g2d::animation::tweener::bind_content(std::size_t keyframe, std::string& content)
{
	this->_content.push_back(g2d::animation::keyframe<std::string>(keyframe, content));
}

void g2d::animation::tweener::bind_hinting(std::size_t keyframe, const g2d::graphic::hinting& hinting)
{
	this->_hinting.push_back(g2d::animation::keyframe<g2d::graphic::hinting>(keyframe, hinting));
}

void g2d::animation::tweener::bind_weight(std::size_t keyframe, const g2d::graphic::weight& weight)
{
	this->_weight.push_back(g2d::animation::keyframe<g2d::graphic::weight>(keyframe, weight));
}

void g2d::animation::tweener::bind_dots(std::size_t keyframe, std::size_t dots)
{
	this->_dots.push_back(g2d::animation::keyframe<std::size_t>(keyframe, dots));
}

void g2d::animation::tweener::bind_index(std::size_t keyframe, std::size_t index)
{
	this->_index.push_back(g2d::animation::keyframe<std::size_t>(keyframe, index));
}

void g2d::animation::tweener::bind_visible(std::size_t keyframe, bool visible)
{
	this->_visible.push_back(g2d::animation::keyframe<bool>(keyframe, visible));
}

void g2d::animation::tweener::bind_wireframe(std::size_t keyframe, bool wireframe)
{
	this->_wireframe.push_back(g2d::animation::keyframe<bool>(keyframe, wireframe));
}

void g2d::animation::tweener::bind_form(std::size_t keyframe, const g2d::graphic::form& form)
{
	this->_form.push_back(g2d::animation::keyframe<g2d::graphic::form>(keyframe, form));
}

void g2d::animation::tweener::bind_flip(std::size_t keyframe, const g2d::graphic::flip& flip)
{
	this->_flip.push_back(g2d::animation::keyframe<g2d::graphic::flip>(keyframe, flip));
}

void g2d::animation::tweener::bind_color(std::size_t keyframe, const g2d::math::color& color)
{
	this->_color.push_back(g2d::animation::keyframe<g2d::math::color>(keyframe, color));
}

void g2d::animation::tweener::bind_pivot(std::size_t keyframe, const g2d::math::point2dd& pivot)
{
	this->_pivot.push_back(g2d::animation::keyframe<g2d::math::point2dd>(keyframe, pivot));
}

void g2d::animation::tweener::bind_position(std::size_t keyframe, const g2d::math::point3dd& position)
{
	this->_position.push_back(g2d::animation::keyframe<g2d::math::point3dd>(keyframe, position));
}

void g2d::animation::tweener::bind_scale(std::size_t keyframe, const g2d::math::size2dd& scale)
{
	this->_scale.push_back(g2d::animation::keyframe<g2d::math::size2dd>(keyframe, scale));
}

void g2d::animation::tweener::bind_rotate(std::size_t keyframe, const g2d::math::rotated& rotate)
{
	this->_rotate.push_back(g2d::animation::keyframe<g2d::math::rotated>(keyframe, rotate));
}

void g2d::animation::tweener::bind_size(std::size_t keyframe, const g2d::math::size2dd& size)
{
	this->_size.push_back(g2d::animation::keyframe<g2d::math::size2dd>(keyframe, size));
}

void g2d::animation::tweener::clear()
{
	this->_measure.clear();
	this->_content.clear();
	this->_hinting.clear();
	this->_weight.clear();
	this->_dots.clear();
	this->_index.clear();
	this->_visible.clear();
	this->_wireframe.clear();
	this->_form.clear();
	this->_flip.clear();
	this->_color.clear();
	this->_pivot.clear();
	this->_position.clear();
	this->_scale.clear();
	this->_rotate.clear();
	this->_size.clear();
}

void g2d::animation::tweener::clear_measure()
{
	this->_measure.clear();
}

void g2d::animation::tweener::clear_content()
{
	this->_content.clear();
}

void g2d::animation::tweener::clear_hinting()
{
	this->_hinting.clear();
}

void g2d::animation::tweener::clear_weight()
{
	this->_weight.clear();
}

void g2d::animation::tweener::clear_dots()
{
	this->_dots.clear();
}

void g2d::animation::tweener::clear_index()
{
	this->_index.clear();
}

void g2d::animation::tweener::clear_visible()
{
	this->_visible.clear();
}

void g2d::animation::tweener::clear_wireframe()
{
	this->_wireframe.clear();
}

void g2d::animation::tweener::clear_form()
{
	this->_form.clear();
}

void g2d::animation::tweener::clear_flip()
{
	this->_flip.clear();
}

void g2d::animation::tweener::clear_color()
{
	this->_color.clear();
}

void g2d::animation::tweener::clear_pivot()
{
	this->_pivot.clear();
}

void g2d::animation::tweener::clear_position()
{
	this->_position.clear();
}

void g2d::animation::tweener::clear_scale()
{
	this->_scale.clear();
}

void g2d::animation::tweener::clear_rotate()
{
	this->_rotate.clear();
}

void g2d::animation::tweener::clear_size()
{
	this->_size.clear();
}

std::size_t g2d::animation::tweener::size_measure() const
{
	return this->_measure.size();
}

std::size_t g2d::animation::tweener::size_content() const
{
	return this->_content.size();
}

std::size_t g2d::animation::tweener::size_hinting() const
{
	return this->_hinting.size();
}

std::size_t g2d::animation::tweener::size_weight() const
{
	return this->_weight.size();
}

std::size_t g2d::animation::tweener::size_dots() const
{
	return this->_dots.size();
}

std::size_t g2d::animation::tweener::size_index() const
{
	return this->_index.size();
}

std::size_t g2d::animation::tweener::size_visible() const
{
	return this->_visible.size();
}

std::size_t g2d::animation::tweener::size_wireframe() const
{
	return this->_wireframe.size();
}

std::size_t g2d::animation::tweener::size_form() const
{
	return this->_form.size();
}

std::size_t g2d::animation::tweener::size_flip() const
{
	return this->_flip.size();
}

std::size_t g2d::animation::tweener::size_color() const
{
	return this->_color.size();
}

std::size_t g2d::animation::tweener::size_pivot() const
{
	return this->_pivot.size();
}

std::size_t g2d::animation::tweener::size_position() const
{
	return this->_position.size();
}

std::size_t g2d::animation::tweener::size_scale() const
{
	return this->_scale.size();
}

std::size_t g2d::animation::tweener::size_rotate() const
{
	return this->_rotate.size();
}

std::size_t g2d::animation::tweener::size_size() const
{
	return this->_size.size();
}

const g2d::animation::keyframe<std::size_t>& g2d::animation::tweener::keyframe_measure(std::size_t index) const
{
	assert(index < this->_measure.size());

	return this->_measure[index];
}

const g2d::animation::keyframe<std::string>& g2d::animation::tweener::keyframe_content(std::size_t index) const
{
	assert(index < this->_content.size());

	return this->_content[index];
}

const g2d::animation::keyframe<g2d::graphic::hinting>& g2d::animation::tweener::keyframe_hinting(std::size_t index) const
{
	assert(index < this->_hinting.size());

	return this->_hinting[index];
}

const g2d::animation::keyframe<g2d::graphic::weight>& g2d::animation::tweener::keyframe_weight(std::size_t index) const
{
	assert(index < this->_weight.size());

	return this->_weight[index];
}

const g2d::animation::keyframe<std::size_t>& g2d::animation::tweener::keyframe_dots(std::size_t index) const
{
	assert(index < this->_dots.size());

	return this->_dots[index];
}

const g2d::animation::keyframe<std::size_t>& g2d::animation::tweener::keyframe_index(std::size_t index) const
{
	assert(index < this->_index.size());

	return this->_index[index];
}

const g2d::animation::keyframe<bool>& g2d::animation::tweener::keyframe_visible(std::size_t index) const
{
	assert(index < this->_visible.size());

	return this->_visible[index];
}

const g2d::animation::keyframe<bool>& g2d::animation::tweener::keyframe_wireframe(std::size_t index) const
{
	assert(index < this->_wireframe.size());

	return this->_wireframe[index];
}

const g2d::animation::keyframe<g2d::graphic::form>& g2d::animation::tweener::keyframe_form(std::size_t index) const
{
	assert(index < this->_form.size());

	return this->_form[index];
}

const g2d::animation::keyframe<g2d::graphic::flip>& g2d::animation::tweener::keyframe_flip(std::size_t index) const
{
	assert(index < this->_flip.size());

	return this->_flip[index];
}

const g2d::animation::keyframe<g2d::math::color>& g2d::animation::tweener::keyframe_color(std::size_t index) const
{
	assert(index < this->_color.size());

	return this->_color[index];
}

const g2d::animation::keyframe<g2d::math::point2dd>& g2d::animation::tweener::keyframe_pivot(std::size_t index) const
{
	assert(index < this->_pivot.size());

	return this->_pivot[index];
}

const g2d::animation::keyframe<g2d::math::point3dd>& g2d::animation::tweener::keyframe_position(std::size_t index) const
{
	assert(index < this->_position.size());

	return this->_position[index];
}

const g2d::animation::keyframe<g2d::math::size2dd>& g2d::animation::tweener::keyframe_scale(std::size_t index) const
{
	assert(index < this->_scale.size());

	return this->_scale[index];
}

const g2d::animation::keyframe<g2d::math::rotated>& g2d::animation::tweener::keyframe_rotate(std::size_t index) const
{
	assert(index < this->_rotate.size());

	return this->_rotate[index];
}

const g2d::animation::keyframe<g2d::math::size2dd>& g2d::animation::tweener::keyframe_size(std::size_t index) const
{
	assert(index < this->_size.size());

	return this->_size[index];
}

bool g2d::animation::tweener::has_tweener() const
{
	return this->has_measure() || this->has_content() || this->has_hinting() || this->has_weight() || this->has_dots() || this->has_index() ||
		this->has_visible() || this->has_wireframe() || this->has_form() || this->has_flip() || this->has_color() || this->has_pivot() ||
		this->has_position() || this->has_scale() || this->has_rotate() || this->has_size();
}

bool g2d::animation::tweener::has_measure() const
{
	return this->_measure.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_content() const
{
	return this->_content.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_hinting() const
{
	return this->_hinting.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_weight() const
{
	return this->_weight.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_dots() const
{
	return this->_dots.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_index() const
{
	return this->_index.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_visible() const
{
	return this->_visible.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_wireframe() const
{
	return this->_wireframe.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_form() const
{
	return this->_form.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_flip() const
{
	return this->_flip.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_color() const
{
	return this->_color.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_pivot() const
{
	return this->_pivot.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_position() const
{
	return this->_position.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_scale() const
{
	return this->_scale.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_rotate() const
{
	return this->_rotate.size() == 0 ? false : true;
}

bool g2d::animation::tweener::has_size() const
{
	return this->_size.size() == 0 ? false : true;
}

std::size_t g2d::animation::tweener::measure()
{
	assert(this->_measure.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value;
	double m_max_value;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_measure.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_measure[i].frame() && m_frame <= this->_measure[n].frame())
		{
			m_min_frame = this->_measure[i].frame();
			m_max_frame = this->_measure[n].frame();
			m_min_value = this->_measure[i].value();
			m_max_value = this->_measure[n].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	std::size_t m_measure = g2d::math::tweening(m_min_value, m_max_value, m_min_frame, m_max_frame, m_frame);

	return m_measure;
}

std::string g2d::animation::tweener::content()
{
	assert(this->_content.size() >= 2);

	std::string m_content;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_content.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_content[i].frame() && m_frame <= this->_content[n].frame())
		{
			m_content = this->_content[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	return m_content;
}

g2d::graphic::hinting g2d::animation::tweener::hinting()
{
	assert(this->_hinting.size() >= 2);

	g2d::graphic::hinting m_hinting;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_hinting.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_hinting[i].frame() && m_frame <= this->_hinting[n].frame())
		{
			m_hinting = this->_hinting[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	return m_hinting;
}

g2d::graphic::weight g2d::animation::tweener::weight()
{
	assert(this->_weight.size() >= 2);

	g2d::graphic::weight m_weight;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_weight.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_weight[i].frame() && m_frame <= this->_weight[n].frame())
		{
			m_weight = this->_weight[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	return m_weight;
}

std::size_t g2d::animation::tweener::dots()
{
	assert(this->_dots.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value;
	double m_max_value;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_dots.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_index[i].frame() && m_frame <= this->_dots[n].frame())
		{
			m_min_frame = this->_dots[i].frame();
			m_max_frame = this->_dots[n].frame();
			m_min_value = this->_dots[i].value();
			m_max_value = this->_dots[n].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	std::size_t m_framer = g2d::math::tweening(m_min_value, m_max_value, m_min_frame, m_max_frame, m_frame);

	return m_framer;
}

std::size_t g2d::animation::tweener::index()
{
	assert(this->_index.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value;
	double m_max_value;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_index.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_index[i].frame() && m_frame <= this->_index[n].frame())
		{
			m_min_frame = this->_index[i].frame();
			m_max_frame = this->_index[n].frame();
			m_min_value = this->_index[i].value();
			m_max_value = this->_index[n].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	std::size_t m_framer = g2d::math::tweening(m_min_value, m_max_value, m_min_frame, m_max_frame, m_frame);

	return m_framer;
}

bool g2d::animation::tweener::visible()
{
	assert(this->_visible.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	bool m_visible = true;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_visible.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame == this->_visible[i].frame())
		{
			m_visible = this->_visible[i].value();
		}
		else if (m_frame == this->_visible[n].frame())
		{
			m_visible = this->_visible[n].value();
		}
		else if (m_frame > this->_visible[i].frame() && m_frame < this->_visible[n].frame())
		{
			m_min_frame = this->_visible[i].frame();
			m_max_frame = this->_visible[n].frame();
			m_tweener = this->_visible[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	assert(m_frame >= m_min_frame && m_frame <= m_max_frame);

	return m_visible;
}

bool g2d::animation::tweener::wireframe()
{
	assert(this->_wireframe.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	bool m_wireframe;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_wireframe.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_wireframe[i].frame() && m_frame <= this->_wireframe[n].frame())
		{
			m_min_frame = this->_wireframe[i].frame();
			m_max_frame = this->_wireframe[n].frame();
			m_wireframe = this->_wireframe[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	assert(m_frame >= m_min_frame && m_frame <= m_max_frame);

	return m_wireframe;
}

g2d::graphic::form g2d::animation::tweener::form()
{
	assert(this->_form.size() >= 2);

	g2d::graphic::form m_form;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_form.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_form[i].frame() && m_frame <= this->_form[n].frame())
		{
			m_form = this->_form[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	return m_form;
}

g2d::graphic::flip g2d::animation::tweener::flip()
{
	assert(this->_flip.size() >= 2);

	g2d::graphic::flip m_flip;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_flip.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_flip[i].frame() && m_frame <= this->_flip[n].frame())
		{
			m_flip = this->_flip[i].value();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	return m_flip;
}

g2d::math::color g2d::animation::tweener::color()
{
	assert(this->_color.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value_r;
	double m_max_value_r;
	double m_min_value_g;
	double m_max_value_g;
	double m_min_value_b;
	double m_max_value_b;
	double m_min_value_a;
	double m_max_value_a;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_color.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_color[i].frame() && m_frame <= this->_color[n].frame())
		{
			m_min_frame = this->_color[i].frame();
			m_max_frame = this->_color[n].frame();
			m_min_value_r = this->_color[i].value().r();
			m_max_value_r = this->_color[n].value().r();
			m_min_value_g = this->_color[i].value().g();
			m_max_value_g = this->_color[n].value().g();
			m_min_value_b = this->_color[i].value().b();
			m_max_value_b = this->_color[n].value().b();
			m_min_value_a = this->_color[i].value().a();
			m_max_value_a = this->_color[n].value().a();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	double m_r = g2d::math::tweening(m_min_value_r, m_max_value_r, m_min_frame, m_max_frame, m_frame);
	double m_g = g2d::math::tweening(m_min_value_g, m_max_value_g, m_min_frame, m_max_frame, m_frame);
	double m_b = g2d::math::tweening(m_min_value_b, m_max_value_b, m_min_frame, m_max_frame, m_frame);
	double m_a = g2d::math::tweening(m_min_value_a, m_max_value_a, m_min_frame, m_max_frame, m_frame);

	return g2d::math::color(m_r, m_g, m_b, m_a);
}

g2d::math::point2dd g2d::animation::tweener::pivot()
{
	assert(this->_pivot.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value_x;
	double m_max_value_x;
	double m_min_value_y;
	double m_max_value_y;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_pivot.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_pivot[i].frame() && m_frame <= this->_pivot[n].frame())
		{
			m_min_frame = this->_pivot[i].frame();
			m_max_frame = this->_pivot[n].frame();
			m_min_value_x = this->_pivot[i].value().x();
			m_max_value_x = this->_pivot[n].value().x();
			m_min_value_y = this->_pivot[i].value().y();
			m_max_value_y = this->_pivot[n].value().y();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	double m_x = g2d::math::tweening(m_min_value_x, m_max_value_x, m_min_frame, m_max_frame, m_frame);
	double m_y = g2d::math::tweening(m_min_value_y, m_max_value_y, m_min_frame, m_max_frame, m_frame);

	return g2d::math::point2dd(m_x, m_y);
}

g2d::math::point3dd g2d::animation::tweener::position()
{
	assert(this->_position.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value_x;
	double m_max_value_x;
	double m_min_value_y;
	double m_max_value_y;
	double m_min_value_z;
	double m_max_value_z;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_position.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_position[i].frame() && m_frame <= this->_position[n].frame())
		{
			m_min_frame = this->_position[i].frame();
			m_max_frame = this->_position[n].frame();
			m_min_value_x = this->_position[i].value().x();
			m_max_value_x = this->_position[n].value().x();
			m_min_value_y = this->_position[i].value().y();
			m_max_value_y = this->_position[n].value().y();
			m_min_value_z = this->_position[i].value().z();
			m_max_value_z = this->_position[n].value().z();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	double m_x = g2d::math::tweening(m_min_value_x, m_max_value_x, m_min_frame, m_max_frame, m_frame);
	double m_y = g2d::math::tweening(m_min_value_y, m_max_value_y, m_min_frame, m_max_frame, m_frame);
	double m_z = g2d::math::tweening(m_min_value_z, m_max_value_z, m_min_frame, m_max_frame, m_frame);

	return g2d::math::point3dd(m_x, m_y, m_z);
}

g2d::math::size2dd g2d::animation::tweener::scale()
{
	assert(this->_scale.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value_w;
	double m_max_value_w;
	double m_min_value_h;
	double m_max_value_h;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_scale.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_scale[i].frame() && m_frame <= this->_scale[n].frame())
		{
			m_min_frame = this->_scale[i].frame();
			m_max_frame = this->_scale[n].frame();
			m_min_value_w = this->_scale[i].value().w();
			m_max_value_w = this->_scale[n].value().w();
			m_min_value_h = this->_scale[i].value().h();
			m_max_value_h = this->_scale[n].value().h();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	double m_w = g2d::math::tweening(m_min_value_w, m_max_value_w, m_min_frame, m_max_frame, m_frame);
	double m_h = g2d::math::tweening(m_min_value_h, m_max_value_h, m_min_frame, m_max_frame, m_frame);

	return g2d::math::size2dd(m_w, m_h);
}

g2d::math::rotated g2d::animation::tweener::rotate()
{
	assert(this->_rotate.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value_h;
	double m_max_value_h;
	double m_min_value_p;
	double m_max_value_p;
	double m_min_value_b;
	double m_max_value_b;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_rotate.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_rotate[i].frame() && m_frame <= this->_rotate[n].frame())
		{
			m_min_frame = this->_rotate[i].frame();
			m_max_frame = this->_rotate[n].frame();
			m_min_value_h = this->_rotate[i].value().h();
			m_max_value_h = this->_rotate[n].value().h();
			m_min_value_p = this->_rotate[i].value().p();
			m_max_value_p = this->_rotate[n].value().p();
			m_min_value_b = this->_rotate[i].value().b();
			m_max_value_b = this->_rotate[n].value().b();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	double m_h = g2d::math::tweening(m_min_value_h, m_max_value_h, m_min_frame, m_max_frame, m_frame);
	double m_p = g2d::math::tweening(m_min_value_p, m_max_value_p, m_min_frame, m_max_frame, m_frame);
	double m_b = g2d::math::tweening(m_min_value_b, m_max_value_b, m_min_frame, m_max_frame, m_frame);

	return g2d::math::rotated(m_h, m_p, m_b);
}

g2d::math::size2dd g2d::animation::tweener::size()
{
	assert(this->_size.size() >= 2);

	std::size_t m_min_frame;
	std::size_t m_max_frame;

	double m_min_value_w;
	double m_max_value_w;
	double m_min_value_h;
	double m_max_value_h;

	std::size_t m_frame = this->_timeline->frame();
	std::size_t m_size = this->_size.size() - 1;
	bool m_tweener = false;

	for (std::size_t i = 0, n = 1; i < m_size; i++, n++)
	{
		if (m_frame >= this->_size[i].frame() && m_frame <= this->_size[n].frame())
		{
			m_min_frame = this->_size[i].frame();
			m_max_frame = this->_size[n].frame();
			m_min_value_w = this->_size[i].value().w();
			m_max_value_w = this->_size[n].value().w();
			m_min_value_h = this->_size[i].value().h();
			m_max_value_h = this->_size[n].value().h();
			m_tweener = true;
		}
	}

	assert(m_tweener == true);

	double m_w = g2d::math::tweening(m_min_value_w, m_max_value_w, m_min_frame, m_max_frame, m_frame);
	double m_h = g2d::math::tweening(m_min_value_h, m_max_value_h, m_min_frame, m_max_frame, m_frame);

	return g2d::math::size2dd(m_w, m_h);
}

