#pragma once

namespace Ff
{
    class Timer
    {
    public:
        void start();
        void end();

        float getDelta() const { return (float)deltaTime; }
    private:
        double startTime{};
        double deltaTime{0.016};
    };
} // namespace Ff