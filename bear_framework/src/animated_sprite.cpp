#include"../include/graphics/animated_sprite.h"

#include<iostream> // @@@@@

using namespace bear;
using namespace bear::graphics;

AnimatedSprite::AnimatedSprite() :
	m_CurrentTick(0),
	m_CurrentKeyframeIndex(0),
	m_TickBreak(0),
	m_IsPlaying(false),
	m_IsLooping(false),
	m_DonePlaying(false)
{

}

void bear::graphics::AnimatedSprite::addKeyframe(AnimatedKeyframe a_Keyframe)
{
	m_Keyframes.push_back(a_Keyframe);
}

void bear::graphics::AnimatedSprite::play()
{
	m_IsPlaying = true;
}

void bear::graphics::AnimatedSprite::stop()
{
	m_IsPlaying = false;
}

void bear::graphics::AnimatedSprite::update(float a_Delta)
{
	if (m_IsPlaying) {
		m_CurrentTick += animation_tick_constant * a_Delta;

		// Are we on the last keyframe?
		if (m_CurrentKeyframeIndex == m_Keyframes.size() - 1) {
			if (m_CurrentTick >= m_TickBreak) {
				reset();
				if(!m_IsLooping)			
					m_IsPlaying = false;
			}
		}
		// Switch to the next keyframe in the line
		if (m_CurrentTick >= m_TickBreak) {
			m_CurrentKeyframeIndex++;
			m_CurrentTick = 0;
		}
	}
	
	m_CurrentTextureName = m_Keyframes[m_CurrentKeyframeIndex].m_TextureName;
}

void bear::graphics::AnimatedSprite::reset()
{
	m_CurrentKeyframeIndex = 0;
	m_CurrentTick = 0;
	m_CurrentTextureName = m_Keyframes[m_CurrentKeyframeIndex].m_TextureName;
}
