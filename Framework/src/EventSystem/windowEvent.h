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
		WindowFocusEvent(int focused)
			: Event(EventType::WINDOW_FOCUS_EVENT)
			, m_focused(focused)
		{

		}

		virtual std::string eventFormat() const override 
		{ 
			return (m_focused) ? std::format("Window focused") : std::format("Window not focused");
		}

	private:
		int m_focused;
	};

	class WindowIconifyEvent : public Event
	{
	public:
		WindowIconifyEvent(int iconified)
			: Event(EventType::WINDOW_ICONIFY_EVENT)
			, m_iconified(iconified)
		{

		}

		virtual std::string eventFormat() const override
		{
			return (m_iconified) ? std::format("Window iconified") : std::format("Window restored");
		}

	private:
		int m_iconified;
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(int maximized)
			: Event(Event::EventType::WINDOW_MAXIMIZE_EVENT)
			, m_maximized(maximized)
		{

		}

		virtual std::string eventFormat() const override
		{
			return (m_maximized) ? std::format("Window maximized") : std::format("Window restored");
		}

	private:
		int m_maximized;
	};

	class CursorEnterEvent : public Event
	{
	public:
		CursorEnterEvent(int entered)
			: Event(EventType::CURSOR_ENTER_EVENT)
			, m_entered(entered)
		{

		}

		virtual std::string eventFormat() const override
		{
			return (m_entered) ? std::format("Cursor entered") : std::format("Cursor left");
		}

	private:
		int m_entered;
	};
}