#pragma once

#include "event.h"

namespace Ff
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: Event(Event::EventType::MOUSE_MOVED_EVENT)
			, m_x(x)
			, m_y(y)
		{
		
		}

		std::string eventFormat() const override { return std::format("x: {}, y: {}", m_x, m_y); }

	private:
		float m_x, m_y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double offset)
			: Event(Event::EventType::MOUSE_SCROLLED_EVENT)
			, m_offset(offset)
		{

		}

		std::string eventFormat() const override { return std::format("offset: {}", m_offset); }
	private:
		double m_offset;

	};

	class MouseButtonPressed : public Event
	{
	public:
		MouseButtonPressed(float button)
			: Event(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT)
			, m_button(button)
		{

		}
		
		std::string eventFormat() const override { return std::format("button: {}", m_button); }
	private:
		float m_button;
	};

	class MouseButtonReleased : public Event
	{
	public:
		MouseButtonReleased(float button)
			: Event(Event::EventType::MOUSE_BUTTON_RELEASED_EVENT)
			, m_button(button)
		{

		}

		std::string eventFormat() const override { return std::format("button: {}", m_button); }
	private:
		float m_button;
	};
}