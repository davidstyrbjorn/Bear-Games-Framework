#include"../include/core/clock.h"

bear::core::Clock::Clock() {
	m_startedAt = 0;
	m_pausedAt = 0;
	m_paused = false;
	m_started = false;
}

bool bear::core::Clock::isStarted() {
	return m_started;
}

bool bear::core::Clock::isStopped() {
	return !m_started;
}

bool bear::core::Clock::isPaused() {
	return m_paused;
}

bool bear::core::Clock::isActive() {
	return !m_paused & m_started;
}

void bear::core::Clock::pause() {
	if (m_paused || !m_started)
		return;

	m_paused = true;
	m_pausedAt = clock();
}

void bear::core::Clock::resume() {
	if (!m_paused)
		return;

	m_paused = false;
	m_startedAt = clock() - m_pausedAt;
}

void bear::core::Clock::stop() {
	m_started = false;
}

void bear::core::Clock::start() {
	if (m_started)
		return;

	m_started = true;
	m_paused = false;
	m_startedAt = clock();
}

void bear::core::Clock::reset() {
	m_paused = false;
	m_startedAt = clock();
}

clock_t bear::core::Clock::getTicks()
{
	if (!m_started)
		return 0;
	if (m_paused)
		return m_pausedAt - m_startedAt;
	return clock() - m_startedAt;
}