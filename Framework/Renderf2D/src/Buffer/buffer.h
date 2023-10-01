#pragma once

namespace Ff
{
    class Buffer
    {
    public:
        Buffer();
        virtual ~Buffer() = default;

    protected:
        unsigned int buffer;
    };
}