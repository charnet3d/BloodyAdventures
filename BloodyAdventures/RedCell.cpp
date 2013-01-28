#include <iostream>
#include "RedCell.h"

using namespace std;

const float RedCell::walkingSpeed = 3;
const float RedCell::jumpSpeed = 10;


RedCell::RedCell(sf::RenderWindow* app, float x, float y)
{
	this->app = app;
	if (!image_r.LoadFromFile("RedCell_Right_HiRes.png"))
        cout << "Error loading RedCell.png" << endl;

	if (!image_l.LoadFromFile("RedCell_Left_HiRes.png"))
        cout << "Error loading RedCell.png" << endl;

	sprite = new AnimatedSprite();

	sprite->setFrameTime(0.08);

	// Walking animation to Left
	listAnim[2].setSpriteSheet(image_l);
	listAnim[2].addFrame(*(new sf::IntRect(276.8, 0, 346, 81)));
	listAnim[2].addFrame(*(new sf::IntRect(207.6, 0, 276.8, 81)));
	listAnim[2].addFrame(*(new sf::IntRect(138.4, 0, 207.6, 81)));
	listAnim[2].addFrame(*(new sf::IntRect(69.2, 0, 138.4, 81)));
	listAnim[2].addFrame(*(new sf::IntRect(0, 0, 69.2, 81)));

	listAnim[2].addFrame(*(new sf::IntRect(276.8, 81, 346, 162)));
	listAnim[0].addFrame(*(new sf::IntRect(207.6, 81, 276.8, 162)));
	listAnim[2].addFrame(*(new sf::IntRect(138.4, 81, 207.6, 162)));
	
	
	// Walking animation to Right
	listAnim[1].setSpriteSheet(image_r);
	listAnim[1].addFrame(*(new sf::IntRect(0, 0, 69.2, 81)));
	listAnim[1].addFrame(*(new sf::IntRect(69.2, 0, 138.4, 81)));
	listAnim[1].addFrame(*(new sf::IntRect(138.4, 0, 207.6, 81)));
	listAnim[1].addFrame(*(new sf::IntRect(207.6, 0, 276.8, 81)));
	listAnim[1].addFrame(*(new sf::IntRect(276.8, 0, 346, 81)));

	listAnim[1].addFrame(*(new sf::IntRect(0, 81, 69.2, 162)));
	listAnim[1].addFrame(*(new sf::IntRect(69.2, 81, 138.4, 162)));
	listAnim[1].addFrame(*(new sf::IntRect(138.4, 81, 207.6, 162)));

	// Standing animation
	listAnim[0].setSpriteSheet(image_r);
	listAnim[0].addFrame(*(new sf::IntRect(207.6, 81, 276.8, 162)));

	sprite->setAnimation(listAnim[0]);
	sprite->play();

	sprite->SetPosition(x, y);
	sprite->SetCenter(0, 0);

	speed.x = 0;
	speed.y = 0;

	movingLeft = false;
	movingRight = false;
	jumping = false;
}

RedCell::RedCell(const RedCell& rCopie)
{
	image_r = rCopie.image_r;
	image_l = rCopie.image_l;

	sprite = new AnimatedSprite(*rCopie.sprite);

	speed = rCopie.speed;

	movingLeft = rCopie.movingLeft;
	movingRight = rCopie.movingRight;
	jumping = rCopie.jumping;
}

RedCell::~RedCell()
{
	delete sprite;
}

AnimatedSprite* RedCell::getSprite()
{
	return sprite;
}

sf::Vector2<float> RedCell::getSpeed()
{
	return speed;
}

void RedCell::setSpeedX(float x)
{
	speed.x = x;
}

void RedCell::setSpeedY(float y)
{
	speed.y = y;
}

void RedCell::setDashPossible(bool dash)
{
	dashPossible = dash;
}

void RedCell::startWalkLeft()
{
	if (!movingLeft)
	{
		sprite->setAnimation(listAnim[2]);
		sprite->play();
	}

	movingLeft = true;
	speed.x = -walkingSpeed;
}

void RedCell::stopWalkLeft()
{
	sprite->setAnimation(listAnim[0]);
	sprite->play();

	movingLeft = false;
}

void RedCell::startWalkRight()
{
	if (!movingRight)
	{
		sprite->setAnimation(listAnim[1]);
		sprite->play();
	}

	movingRight = true;
	speed.x = walkingSpeed;
}

void RedCell::stopWalkRight()
{
	sprite->setAnimation(listAnim[0]);
	sprite->play();

	movingRight = false;
}

void RedCell::walk()
{
	if (movingLeft || movingRight)
		sprite->Move(speed.x, 0);
}

void RedCell::startJump()
{
	if (speed.y == 0)
	{
		jumping = true;
		speed.y = jumpSpeed;
	}
}

void RedCell::jump()
{
	speed.y -= 0.5f;
	sprite->Move(0, -speed.y);

	if (speed.y <= 0)
	{
		speed.y = 0;
		jumping = false;
	}
}


bool RedCell::isJumping()
{
	return jumping;
}

bool RedCell::isMovingLeft()
{
	return movingLeft;
}

bool RedCell::isMovingRight()
{
	return movingRight;
}

bool RedCell::getDashPossible()
{
	return dashPossible;
}