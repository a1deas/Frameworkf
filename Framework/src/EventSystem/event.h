#pragma once

#include <string>

#include "Core/log.h"

namespace Ff
{
	class Event
	{
	public:
		enum class EventType : int8_t
		{
			MOUSE_BUTTON_PRESSED_EVENT = 1,
			MOUSE_BUTTON_RELEASED_EVENT,

			MOUSE_MOVED_EVENT,
			MOUSE_SCROLLED_EVENT,

			KEY_RELEASED_EVENT,
			KEY_REPEATED_EVENT,
			KEY_PRESSED_EVENT,

			WINDOW_RESIZE_EVENT,
			WINDOW_CLOSED_EVENT,
		};

	protected:
		constexpr Event(EventType type)
			: m_type(type)
		{

		}
	
	public:
		virtual ~Event() = default;

		virtual std::string eventFormat() const = 0;

		inline EventType getType() const { return m_type; }

		constexpr std::string_view getEventStr()
		{
			switch (m_type)
			{
				case EventType::MOUSE_BUTTON_PRESSED_EVENT:
					return "MOUSE_BUTTON_PRESSED";
				case EventType::MOUSE_BUTTON_RELEASED_EVENT:
					return "MOUSE_BUTTON_RELEASED";
				case EventType::MOUSE_MOVED_EVENT:
					return "MOUSE_MOVED";
				case EventType::MOUSE_SCROLLED_EVENT:
					return "MOUSE_SCROLLED";
				case EventType::KEY_RELEASED_EVENT:
					return "KEY_RELEASED";
				case EventType::KEY_REPEATED_EVENT:
					return "KEY_REPEATED";
				case EventType::KEY_PRESSED_EVENT:
					return "KEY_PRESSED";
				case EventType::WINDOW_RESIZE_EVENT:
					return "WINDOW_RESIZE";
				case EventType::WINDOW_CLOSED_EVENT:
					return "WINDOW_CLOSED";
				default:
					FFERROR("UNKNOWN EVENT");
					return "UNKNOWN_EVENT";
			}
		}

	protected:
		EventType m_type;
	};
}