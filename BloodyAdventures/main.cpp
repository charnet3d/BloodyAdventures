#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Image imgBackground;
    if (!imgBackground.LoadFromFile("background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprtBackground(imgBackground);
    sprtBackground.SetScale(App.GetWidth() / sprtBackground.GetSize().x, App.GetHeight() / sprtBackground.GetSize().y);

    sf::Image imgRedCell;
    if (!imgRedCell.LoadFromFile("RedCell.png"))
        return EXIT_FAILURE;

    sf::Sprite sprtRedCell(imgRedCell);
    sprtRedCell.SetCenter(sprtRedCell.GetSize().x / 2, sprtRedCell.GetSize().y);
    sprtRedCell.SetPosition(App.GetDefaultView().GetCenter().x, App.GetDefaultView().GetCenter().y);
    //const sf::Input& input = App.GetInput();

    sf::Font MyFont;

    // Chargement à partir d'un fichier sur le disque
    if (!MyFont.LoadFromFile("arial.ttf"))
        return EXIT_FAILURE;

    sf::String Text("Bloody Adventures Prototype", MyFont, 20);
	Text.SetColor(sf::Color::Black);

	// The ground
	sf::Shape groundLine = sf::Shape::Line(0, 500, 800, 500, 2, sf::Color::Black);

	float ySpeed = 0.0;
	float xSpeed = 2;
	bool jumping = false;
	bool moveLeft = false;
	bool moveRight = false;

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
				case sf::Key::Z:
					if (ySpeed == 0)
					{
						jumping = true;
						ySpeed = 4;
					}
					break;
				case sf::Key::Left:
					moveLeft = true;
					
					break;
				case sf::Key::Right:
					moveRight = true;
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
					moveLeft = false;
					break;
				case sf::Key::Right:
					moveRight = false;
					break;
				default:
					break;
				}
			}
        }

		if (moveLeft)
			sprtRedCell.Move(-xSpeed, 0);

		if (moveRight)
			sprtRedCell.Move(xSpeed, 0);

		// Check if object is above the ground it has to go back down
		if (sprtRedCell.GetPosition().y < groundLine.GetPointPosition(0).y && !jumping)
		{
			ySpeed += 0.05;
			sprtRedCell.Move(0, ySpeed);
		}
		else if (ySpeed != 0 && !jumping)
			ySpeed = 0;

		if (jumping)
		{
			ySpeed -= 0.05;
			sprtRedCell.Move(0, -ySpeed);

			if (ySpeed <= 0)
			{
				ySpeed = 0;
				jumping = false;
			}
		}


        // Clear screen
        App.Clear();

        // Draw the sprite
        App.Draw(sprtBackground);
        App.Draw(Text);
		App.Draw(sprtRedCell);

		App.Draw(groundLine);

        // Update the window
        App.Display();
    }

    return EXIT_SUCCESS;
}
