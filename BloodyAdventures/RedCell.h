#ifndef _REDCELL_H_
#define _REDCELL_H_

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "main.h"

class RedCell
{
private:
	sf::RenderWindow* app;

	sf::Image image_r;
	sf::Image image_l;
	AnimatedSprite* sprite;

	Animation listAnim[3];

	sf::Vector2<float> speed;
	
	bool movingLeft;
	bool movingRight;
	bool jumping;

	bool dashPossible;
public:

	static const float walkingSpeed;
	static const float jumpSpeed;

	RedCell(sf::RenderWindow* app, float x = 0, float y = 0);
	RedCell(const RedCell& rCopie);
    ~RedCell();

	AnimatedSprite* getSprite();

	sf::Vector2<float> getSpeed();

	void setSpeedX(float x);
	void setSpeedY(float y);
	void setDashPossible(bool dash);

	void startWalkLeft();
	void stopWalkLeft();

	void startWalkRight();
	void stopWalkRight();

	void walk();

	void startJump();
	void jump();

	bool isJumping();
	bool isMovingLeft();
	bool isMovingRight();
	bool getDashPossible();
};

#endif // _REDCELL_H_