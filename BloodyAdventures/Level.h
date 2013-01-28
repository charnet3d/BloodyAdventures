#ifndef _REDCELL_H_
#define _REDCELL_H_

#include <SFML/Graphics.hpp>

#include <iostream>

class Level
{
private:
	char** levelArray;
	int width;
	int height;

public:
	Level(std::string file);

	void draw(sf::RenderWindow & app);
};


#endif // _REDCELL_H_