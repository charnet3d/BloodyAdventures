////////////////////////////////////////////////////////////
//
// Copyright (C) 2013 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(float frameTime, bool paused, bool looped) :
    m_animation(NULL), m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused), m_isLooped(looped)
{

}

void AnimatedSprite::setAnimation(const Animation& animation)
{
    m_animation = &animation;
	this->SetImage(*animation.getSpriteSheet());
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}

void AnimatedSprite::play()
{
    if(m_isPaused)
    {
        m_currentTime = 0.f;
        m_isPaused = false;
    }
}

void AnimatedSprite::pause()
{
    m_isPaused = true;
}

void AnimatedSprite::stop()
{
    m_isPaused = true;
    m_currentFrame = 0;
}

void AnimatedSprite::setLooped(bool looped)
{
    m_isLooped = looped;
}

bool AnimatedSprite::isLooped() const
{
    return m_isLooped;
}

bool AnimatedSprite::isPlaying() const
{
    return !m_isPaused;
}

float AnimatedSprite::getFrameTime() const
{
    return m_frameTime;
}

void AnimatedSprite::setFrame(std::size_t newFrame, bool resetTime)
{
    if(m_animation)
    {
        //calculate new vertex positions and texture coordiantes
        sf::IntRect rect = m_animation->getFrame(m_currentFrame);

		this->SetSubRect(rect);
    }

    if(resetTime)
        m_currentTime = 0.f;
}

void AnimatedSprite::setFrameTime(float time)
{
	m_frameTime = time;
}

void AnimatedSprite::update(float deltaTime)
{
    // if not paused and we have a valid animation
    if(!m_isPaused && m_animation)
    {
        // add delta time
        m_currentTime += deltaTime;

        // if current time is bigger then the frame time advance one frame
        if(m_currentTime >= m_frameTime)
        {
            // reset time
            m_currentTime = 0.f;

            // get next Frame index
            if(m_currentFrame + 1 < m_animation->getSize())
                m_currentFrame++;
            else
            {
                // animation has ended
                m_currentFrame = 0; // reset to start

                if(!m_isLooped)
                {
                    m_isPaused = true;
                }

            }

            // set the current frame, not reseting the time
            setFrame(m_currentFrame, false);
        }
    }
}