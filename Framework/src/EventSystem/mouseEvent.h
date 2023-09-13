#pragma once

#include "event.h"

namespace Ff
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int x, int y)
			: Event(Event::EventType::MOUSE_MOVED_EVENT)
			, m_x(x)
			, m_y(y)
		{
		
		}

		std::string eventFormat() const override { return std::format("x: {}, y: {}", m_x, m_y); }

	private:
		int m_x, m_y;
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
}