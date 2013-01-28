#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "RedCell.h"
#include "TimerInterval.h"
#include "main.h"

using namespace std;

sf::Clock mainTimer;

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");

	App.SetFramerateLimit(60);
	//App.UseVerticalSync(false);

    // Load a sprite to display
    sf::Image imgBackground;
    if (!imgBackground.LoadFromFile("background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprtBackground(imgBackground);
    sprtBackground.SetScale(App.GetWidth() / sprtBackground.GetSize().x, App.GetHeight() / sprtBackground.GetSize().y);

    sf::Font MyFont;

    // Chargement à partir d'un fichier sur le disque
    if (!MyFont.LoadFromFile("arial.ttf"))
        return EXIT_FAILURE;

    sf::String Text("Z: Jump, A: Dash", MyFont, 20);
	Text.SetColor(sf::Color::Black);

	sf::String Text2("To dash you need to syncronise with the end of the heart beat", MyFont, 20);
	Text2.SetPosition(0, Text.GetRect().Bottom + 5);
	Text2.SetColor(sf::Color::Black);

	// The ground
	sf::Shape groundLine = sf::Shape::Line(0, 500, 800, 500, 2, sf::Color::Black);
	
	// The player
	RedCell* player = new RedCell(&App, App.GetDefaultView().GetCenter().x, App.GetDefaultView().GetCenter().y);

	TimerInterval timerHeartBeat(1.5);
	sf::Shape heartBeatPanel = sf::Shape::Rectangle(0, Text2.GetRect().Bottom + 5, 800, 20 + Text2.GetRect().Bottom + 5, sf::Color::Black, 1, sf::Color::Red);
	sf::Shape heartBeatGauge = sf::Shape::Rectangle(0, Text2.GetRect().Bottom + 5, 0, 20 + Text2.GetRect().Bottom + 5, sf::Color::Red);

	//sf::Shape testPanel = sf::Shape::Rectangle(0, 30, 800, 50, sf::Color::Black, 1, sf::Color::Red);

	float currentHeartBeat = 0;
	
	timerHeartBeat.demarre();
	mainTimer.Reset();

	// Start the game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)// Bouton X
                App.Close();

			if (Event.Type == sf::Event::KeyPressed)
			{
				switch (Event.Key.Code)
				{
				case sf::Key::Escape:
					App.Close();
					break;
				case sf::Key::A:		// Dash
					if (player->getDashPossible() && currentHeartBeat > (0.5f * timerHeartBeat.getInterval()))
					{
						player->getSprite()->setFrameTime(0.02);

						// syncronisation doit etre à la fin d'un battement de coeur (80%)
						if (player->isMovingLeft())
							player->setSpeedX(-player->walkingSpeed - 10);
						else if (player->isMovingRight())
							player->setSpeedX(player->walkingSpeed + 10);
					}
					player->setDashPossible(false);
					break;
				case sf::Key::Z:		// Jump
					player->startJump();
					break;
				case sf::Key::Left:
					player->startWalkLeft();
					break;
				case sf::Key::Right:
					player->startWalkRight();
					break;
				default:
					break;
				}
			}

			if (Event.Type == sf::Event::KeyReleased)
			{
				switch (Event.Key.Code)
				{
				case sf::Key::Left:
					player->stopWalkLeft();
					break;
				case sf::Key::Right:
					player->stopWalkRight();
					break;
				case sf::Key::A:

					break;
				default:
					break;
				}
			}
        }

		player->walk();
		if (player->isJumping())
			player->jump();

		// Check if object is above the ground it has to go back down
		if (((player->getSprite()->GetPosition().y + player->getSprite()->GetSize().y) + 5) < groundLine.GetPointPosition(0).y && !player->isJumping())
		{
			player->setSpeedY(player->getSpeed().y + 0.5f);
			player->getSprite()->Move(0, player->getSpeed().y);
		}
		else if (player->getSpeed().y != 0 && !player->isJumping())
		{
			player->getSprite()->SetPosition(player->getSprite()->GetPosition().x, groundLine.GetPointPosition(0).y - player->getSprite()->GetSize().y);
			player->setSpeedY(0);
		}

		// Check if the player has accelerated with a dash, if so we decelerate to the walking speed
		if (abs(player->getSpeed().x) > player->walkingSpeed)
		{
			player->getSprite()->setFrameTime(player->getSprite()->getFrameTime() + 0.01);

			if (player->getSprite()->getFrameTime() >= 0.08)
			{
				player->getSprite()->setFrameTime(0.08);
			}

			if (player->isMovingLeft())
			{
				player->setSpeedX(player->getSpeed().x + 0.5f);

				if (abs(player->getSpeed().x) <= player->walkingSpeed)
					player->setSpeedX(-player->walkingSpeed);
			}
			else if (player->isMovingRight())
			{
				player->setSpeedX(player->getSpeed().x - 0.5f);

				if (abs(player->getSpeed().x) <= player->walkingSpeed)
					player->setSpeedX(player->walkingSpeed);
			}
		}
		else if (!player->isMovingLeft() && !player->isMovingRight())
		{
			// player needs to decelerate until he stops
			
			if (player->getSpeed().x > 0)
				player->setSpeedX(player->getSpeed().x - 0.5f);
			else if (player->getSpeed().x < 0)
				player->setSpeedX(player->getSpeed().x + 0.5f);
			
			if (abs(player->getSpeed().x) < 0.5f)
				player->setSpeedX(0);
		}
		

		if (timerHeartBeat.verifie(currentHeartBeat))
			player->setDashPossible(true);
		heartBeatGauge.SetPointPosition(1, 800 * (currentHeartBeat / timerHeartBeat.getInterval()), heartBeatGauge.GetPointPosition(1).y);
		heartBeatGauge.SetPointPosition(2, 800 * (currentHeartBeat / timerHeartBeat.getInterval()), heartBeatGauge.GetPointPosition(2).y);

        // Clear screen
        App.Clear();

        // Draw the sprite
        App.Draw(sprtBackground);
		App.Draw(heartBeatPanel);
		App.Draw(heartBeatGauge);

		//App.Draw(testPanel);

        App.Draw(Text);
		App.Draw(Text2);
		player->getSprite()->update(App.GetFrameTime());

		App.Draw(groundLine);

		App.Draw(*player->getSprite());

        // Update the window
        App.Display();

		mainTimer.Reset();
    }

    return EXIT_SUCCESS;
}
