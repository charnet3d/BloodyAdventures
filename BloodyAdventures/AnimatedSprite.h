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

#ifndef ANIMATEDSPRITE_INCLUDE
#define ANIMATEDSPRITE_INCLUDE

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.h"

#include <iostream>

class AnimatedSprite : public sf::Sprite
{
public:
    explicit AnimatedSprite(float frameTime = 0.2f, bool paused = false, bool looped = true);

    void update(float deltaTime);
    void setAnimation(const Animation& animation);
    void play();
    void pause();
    void stop();
    void setLooped(bool looped);
    bool isLooped() const;
    bool isPlaying() const;
    float getFrameTime() const;
    void setFrame(std::size_t newFrame, bool resetTime = true);

	void setFrameTime(float time);

private:
    const Animation* m_animation;
    float m_frameTime;
    float m_currentTime;
    std::size_t m_currentFrame;
    bool m_isPaused;
    bool m_isLooped;
    const sf::Image* m_image;

};

#endif // ANIMATEDSPRITE_INCLUDE