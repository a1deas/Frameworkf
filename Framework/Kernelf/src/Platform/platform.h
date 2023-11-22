#pragma once

namespace Ff
{
    /**
     * Platform - singleton class(with the one and only instance). 
     * Represents user's interaction with events and other platform-specific operations.
     */
    class Platform
    {
    private:
        static Platform* s_Singleton;

    public:
        Platform();
        ~Platform();

        /** Input and handle events. */
        void pollEvents() const;

        /** Get platform instance. */
        static Platform* get() { return s_Singleton; }
    };
} // namespace Ff