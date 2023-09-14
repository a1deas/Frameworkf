#pragma once

#include "event.h"
#include "enumKey.h"

class KeyReleasedEvent;

namespace Ff
{
	class KeyPressedEvent : public Event
	{
	public:

		KeyPressedEvent(Key key)
			: Event(EventType::KEY_PRESSED_EVENT)
			, m_key(key)
		{

		}

		std::string eventFormat() const override { return std::format("key: {}", getKeyString(m_key)); }
	private:
		Key m_key;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(Key key)
			: Event(EventType::KEY_RELEASED_EVENT)
			, m_key(key)
		{

		}

		std::string eventFormat() const override { return std::format("key: {}", getKeyString(m_key)); }
	private:
		Key m_key;
	};

	class KeyRepeatedEvent : public Event
	{
	public:

		KeyRepeatedEvent(Key key)
			: Event(EventType::KEY_REPEATED_EVENT)
			, m_key(key)
		{

		}

		std::string eventFormat() const override { return std::format("key: {}", getKeyString(m_key)); }
	private:
		Key m_key;
	};
}
