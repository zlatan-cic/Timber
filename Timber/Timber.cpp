#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>


using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object VideoMode vm(1920, 1080)
	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Timber!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU Textur
	Texture textureBackground;

	//// Load a graphic into the texture
	/*textureBackground.loadFromFile("graphics/background.png");*/
	if (!textureBackground.loadFromFile("graphics/background.png"))
	{
		std::cout << "Faild to load background image\n";
	}

	// Create a sprite
	Sprite spriteBackground;

	//// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	/// Set the spriteBackground to cover the screen spriteBackground.setPosition(0, 0);
	spriteBackground.setPosition(0, 0);

	// // // /// /// /// /// /// 
	// Make a tree sprite // /// 
	// /// /// /// /// /// // /// 
	const float TREE_HORIZONTAL_POSITION = 810;
	const float TREE_VERTICAL_POSITION = 0;
	Texture textureTree;
	/*textureTree.loadFromFile("graphics/tree.png");*/
	if (!textureTree.loadFromFile("graphics/tree.png"))
	{
		std::cout << "Faild to load Tree image\n";
	}
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION);

	// // // /// BEE /// /// /// /// 
	// 
	// Making bee flay in wawes
	// 
	float beeX = 2000.0f;
	float beeBaseHeight = 600.f;
	float beeWaweAmplitude = 50.0f;
	float beeWaweFrequency = 0.02f;



	// Make a bee sprite // /// 
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// IS the Bee currently moving
	bool beeActive = false;
	// How fast can it flay
	float beeSpede = 0.0f;

	// // // /// /// /// /// /// 
	// Make a cloud  sprite // /// 
	// make 3 cloud sprites from 1 textur
	Texture textureCloud;

	// Load first new texture;
	if (!textureCloud.loadFromFile("graphics/cloud.png"))
	{
		std::cout << "Faild to load cloud image\n";
	}
	// 3 new sprites whit the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	// Position the clouds on the left of the screen
	// at different heights
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;


	//Var to control time itself;
	Clock clock;

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2,980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track whether the game is running
	bool paused = true;

	// Draw some text
	int score = 0;
	Text messageText;
	Text scoreText;

	//Wn need to chouse a font 
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Set the font yo our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assing the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(
		textRect.left + textRect.width / 2.0f, 
		textRect.top + textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);


	while (window.isOpen())
	{
		/*
			****************************************
			Handle the players input
			****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			// Reset the time and the score
			score = 0;
			timeRemaining = 6;
		}

		/*
		******** Update the scene
		*/

		if (!paused)
		{
			//Measure time
			Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();
			//size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f)
			{
				//Pause the game
				paused = true;

				//change the message shows to the player
				messageText.setString("Out of time!!");
				
				//reposition the text message on its nre size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(
					textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);


			}


			/*Setap the bee*/
			/*if (!beeActive)
			{
				//How fast will it go
				srand((int)time(0));
				beeSpede = (rand() % 200) + 200;

				// How high is the bee
				srand((int)time(0));
				float height = (rand() % 500) + 600;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			/// move the bee
			{
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpede * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Has the bee reach the left-hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					//Set it up to be a whole new bee next frame
					beeActive = false;
				}
			}*/
			if (!beeActive)
			{
				beeSpede = (rand() % 200) + 200;
				beeBaseHeight = (rand() % 400) + 300;
				beeX = 2000.0f;
				beeActive = true;
			}
			else
			{
				beeX -= beeSpede * dt.asSeconds();
				float beeY = beeWaweAmplitude * sin(beeWaweFrequency * beeX) + beeBaseHeight;
				spriteBee.setPosition(beeX, beeY);
				if (beeX < -100)
				{
					beeActive = false;
				}
			}

			// Manage the clouds
			// cloud 1
			if (!cloud1Active)
			{
				// how fast is cloud1 going
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				//How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
				// Has the cloud reach the right hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					cloud1Active = false;
				}
				;
			}

			//cloud 2
			if (!cloud2Active)
			{
				// how fast is cloud1 going
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y
				);
				if (spriteCloud2.getPosition().x > 1920)
				{
					cloud2Active = false;
				}
			}

			// Cloud 3 
			if (!cloud3Active)
			{
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int)time(0) % 200);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y
				);
				if (spriteCloud3.getPosition().x > 1920)
				{
					cloud3Active = false;
				}
			}
		}

		
		// Update the score text
		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());

		// Clear everything from the last frame window.clear();
		window.clear();

		/*
		****************************************
		Draw the scene
		****************************************
		*/



		// Draw our game scene here
		window.draw(spriteBackground);
		

		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		// Draw the tree
		window.draw(spriteTree);
		// Draw the Bee
		window.draw(spriteBee);

		//draw the timebar
		window.draw(timeBar);

		window.draw(scoreText);
		if (paused)
		{
			window.draw(messageText);
		}

		// Show everything we just drew window.display();
		window.display();



	}

	
	
	return 0;
}