#include "TimerInterval.h"

#include <iostream>

TimerInterval::TimerInterval(float interval) : Timer(), m_Interval(interval)
{
    demarre();
    m_DernierTemps = getTemps();
}

bool TimerInterval::verifie()
{
	float tmp;
	return verifie(tmp);
}

bool TimerInterval::verifie(float& timePassed)
{
	timePassed = getTemps() - m_DernierTemps;

    if (m_Interval && (timePassed > m_Interval))
    {
        m_DernierTemps = getTemps();
        return true;
    }
    else
        return false;
}

float TimerInterval::getInterval()
{
	return m_Interval;
}