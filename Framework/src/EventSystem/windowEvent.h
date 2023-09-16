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

		virtual	std::string eventFormat() const override { return std::format("Window resize({}, {})", m_width, m_height); }

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
		virtual std::string eventFormat() const override { return std::format("Window closed");
		};
	};

	class WindowPositionEvent : public Event
	{
	public:
		WindowPositionEvent(int xpos, int ypos)
			: Event(Event::EventType::WINDOW_POSITION_EVENT)
			, m_xpos(xpos)
			, m_ypos(ypos)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Window changed position to: {}, {}", m_xpos, m_ypos); }
	
	private:
		int m_xpos, m_ypos;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent()
			: Event(EventType::WINDOW_FOCUS_EVENT)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Window focused"); }
	};

	class WindowUnfocusEvent : public Event
	{
	public: 
		WindowUnfocusEvent()
			: Event(EventType::WINDOW_UNFOCUS_EVENT)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Window unfocused"); }
	};

	class WindowIconifyEvent : public Event
	{
	public:
		WindowIconifyEvent()
			: Event(EventType::WINDOW_ICONIFY_EVENT)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Window iconified"); }
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent()
			: Event(Event::EventType::WINDOW_MAXIMIZE_EVENT)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Window maximized"); }
	};

	class WindowRestoredEvent : public Event
	{
	public: 
		WindowRestoredEvent()
			: Event(Event::EventType::WINDOW_RESTORE_EVENT)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Window restored"); }
	};
}