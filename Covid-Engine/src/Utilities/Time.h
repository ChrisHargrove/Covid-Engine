#pragma once

#include <chrono>

using std::chrono::high_resolution_clock;

namespace Covid
{
	class Time
	{
	public:
		Time() :
			m_deltaTime(0),
			m_timeSinceStartup(0)
		{
			m_appStartTime = high_resolution_clock::now();
			m_previousFrameStartTime = m_appStartTime;
		}

		~Time()
		{
		}

		void Update()
		{
			high_resolution_clock::time_point currentTimePoint = high_resolution_clock::now();
			m_timeSinceStartup = std::chrono::duration_cast<std::chrono::duration<long>>(currentTimePoint - m_appStartTime).count();
			m_deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint - m_previousFrameStartTime).count();
			m_previousFrameStartTime = currentTimePoint;
		}

		float GetDeltaTime()
		{
			return m_deltaTime;
		}

		long GetTimeSinceStartup()
		{
			return m_timeSinceStartup;
		}


	private:
		float m_deltaTime;
		long m_timeSinceStartup;

		high_resolution_clock::time_point m_previousFrameStartTime;
		high_resolution_clock::time_point m_appStartTime;
	};
}