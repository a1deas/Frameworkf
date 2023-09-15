#pragma once
#include "event.h"

namespace Ff
{
	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int width, int height)
			: Event(EventType::WINDOW_RESIZE_EVENT)
			, m_width(width)
			, m_height(height)
		{

		}

		std::string eventFormat() const override { return std::format("Window resize({}, {})", m_width, m_height); }

	private:
		int m_width, m_height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
			: Event(Event::EventType::WINDOW_CLOSED_EVENT)
		{

		}
		std::string eventFormat() const override {
			return std::format("Window closed");
		};
	};
}