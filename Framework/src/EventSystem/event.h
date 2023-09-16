#pragma once

#include "Core/log.h"
#include <string>

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
			CURSOR_ENTER_EVENT,
			CURSOR_LEFT_EVENT,

			KEY_PRESSED_EVENT,
			KEY_RELEASED_EVENT,
			KEY_REPEATED_EVENT,
			TEXT_INPUT_EVENT,

			WINDOW_RESIZE_EVENT,
			WINDOW_CLOSED_EVENT,
			WINDOW_POSITION_EVENT,
			WINDOW_FOCUS_EVENT,
			WINDOW_UNFOCUS_EVENT,
			WINDOW_ICONIFY_EVENT,
			WINDOW_MAXIMIZE_EVENT,
			WINDOW_RESTORE_EVENT,
			
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

		constexpr std::string_view getEventStr() const 
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
				case EventType::TEXT_INPUT_EVENT:
					return "TEXT_INPUT";
				case EventType::WINDOW_RESIZE_EVENT:
					return "WINDOW_RESIZE";
				case EventType::WINDOW_CLOSED_EVENT:
					return "WINDOW_CLOSED";
				case EventType::WINDOW_POSITION_EVENT:
					return "WINDOW_POS";
				case EventType::WINDOW_FOCUS_EVENT:
					return "WINDOW_FOCUS";
				case EventType::WINDOW_ICONIFY_EVENT:
					return "WINDOW_ICONIFY";
				case EventType::WINDOW_MAXIMIZE_EVENT:
					return "WINDOW_MAXIMIZE";
				case EventType::CURSOR_ENTER_EVENT:
					return "CURSOR_ENTER";
				case EventType::CURSOR_LEFT_EVENT:
					return "CURSOR_LEFT";
				case EventType::WINDOW_UNFOCUS_EVENT:
					return "WINDOW_UNFOCUS";
				case EventType::WINDOW_RESTORE_EVENT:
					return "WINDOW_RESTORE";
				default:
					FFERROR("UNKNOWN EVENT");
					return "UNKNOWN_EVENT";
			}
		}

	protected:
		EventType m_type;
	};
}