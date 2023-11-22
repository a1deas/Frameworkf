#pragma once

namespace Ff
{
    class Timer
    {
    public:
        /** Start timer and save start time. */
        void start();
        /** End timer, save end time and calculate delta. */
        void end();

        /** Get delta time, the completion time in seconds since the last frame. */
        float getDelta() const { return (float)m_DeltaTime; }
    private:
        double m_StartTime{};
        double m_DeltaTime{0.016};
    };
} // namespace Ff