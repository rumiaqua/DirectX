# include "Stopwatch.hpp"

using namespace std::chrono;

Stopwatch::Stopwatch()
	: m_isRunning(false)
	, m_clock()
	, m_start()
	, m_end()
{

}

void Stopwatch::Start()
{
	if (m_start == false)
	{
		Restart();
	}

	m_isRunning = true;
}

void Stopwatch::Restart()
{
	m_start = m_clock.now();

	Start();
}

void Stopwatch::Stop()
{
	m_end = m_clock.now();

	m_isRunning = false;
}

Stopwatch::Duration Stopwatch::ElapsedDuration() const
{
	return duration_cast<Duration>(m_end - *m_start);
}

long long Stopwatch::Elapsed() const
{
	return ElapsedDuration().count();
}
