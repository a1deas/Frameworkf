#pragma once

#include "event.h"
#include "enumButton.h"

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

		virtual std::string eventFormat() const override { return std::format("x: {}, y: {}", m_x, m_y); }

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

		virtual std::string eventFormat() const override { return std::format("offset: {}", m_offset); }
	private:
		double m_offset;

	};

	class MouseButtonPressed : public Event
	{
	public:
		MouseButtonPressed(MouseButton button)
			: Event(Event::EventType::MOUSE_BUTTON_PRESSED_EVENT)
			, m_button(button)
		{

		}
		
		virtual std::string eventFormat() const override { return std::format("button: {}", getButtonString(m_button)); }
	private:
		MouseButton m_button;
	};

	class MouseButtonReleased : public Event
	{
	public:
		MouseButtonReleased(MouseButton button)
			: Event(Event::EventType::MOUSE_BUTTON_RELEASED_EVENT)
			, m_button(button)
		{

		}

		virtual std::string eventFormat() const override { return std::format("button: {}", getButtonString(m_button)); }
	private:
		MouseButton m_button;
	};

	class CursorEnterEvent : public Event
	{
	public:
		CursorEnterEvent()
			: Event(EventType::CURSOR_ENTER_EVENT)
		{

		}

		virtual std::string eventFormat() const override { return std::format("Cursor entered"); }
	};

	class CursorLeftEvent : public Event
	{
	public:
		CursorLeftEvent()
			: Event(EventType::CURSOR_LEFT_EVENT)
		{ 

		}

		virtual std::string eventFormat() const override { return std::format("Cursor left"); }
	};
}