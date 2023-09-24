#pragma once

namespace Ff
{
    class Platform
    {
        static Platform* Singleton;

    public:
        Platform();
        ~Platform();

        void pollEvents() const;

        static Platform* get() { return Singleton; }
    };
} // namespace Ff