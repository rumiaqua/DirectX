# pragma once

# include "Optional/Optional.hpp"

# include <chrono>

class Stopwatch
{
private:

	using Clock = std::chrono::system_clock;

	using Duration = std::chrono::milliseconds;

	using TimePoint = std::chrono::time_point<Clock>;

public:

	Stopwatch();

	void Start();

	void Restart();

	void Stop();

	Duration ElapsedDuration() const;

	long long Elapsed() const;

private:

	bool m_isRunning;

	Clock m_clock;

	Optional<TimePoint> m_start;

	TimePoint m_end;
};
