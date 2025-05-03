#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the player/branch
// left or right
enum class side {LEFT,RIGHT,NONE};
side branchPositions[NUM_BRANCHES];


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

	//Prepare 5 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	
	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead centure
		//We can then use spin it round without changing its position;
		branches[i].setOrigin(220, 20);
	}

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);

	// Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	//The player starts on the left
	side playerSide = side::LEFT;

	// Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	//Control the player input
	bool acceptInput = false;


	while (window.isOpen())
	{
		/*
			****************************************
			Handle the players input
			****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				//hide the axe 
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}


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

			//Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			//Make sure the grave stone is hidden
			spriteRIP.setPosition(675, 2000);
			/// Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;
		}

		// Wrap the player controls to
		// Make sure we are accepting inpu
		if (acceptInput)
		{
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				//Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;

				//Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(1200, 720);

				//Update the branch
				updateBranches(score);

				//set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;
			}


			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(580, 720);

				// update the branches
				updateBranches(score);

				// set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;
			}

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
			// Handle a flying log
			if (logActive)
			{
				spriteLog.setPosition(
					spriteLog.getPosition().x +
					(logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y +
					(logSpeedY * dt.asSeconds()));

				//Has the log reach right angle
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().y > 2000)
				{
					//Set ti up ready to ber a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}
			if (branchPositions[5] == playerSide)
			{
				//death
				paused = true;
				acceptInput = false;

				//Draw the grave stone
				spriteRIP.setPosition(525, 760);

				//hide the player
				spritePlayer.setPosition(2000, 660);

				// Change the text of the message
				messageText.setString("SQUISHED!!");

				//Cneter text on the scren
				FloatRect text = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

			}
		}

		
		// Update the score text
		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());

		//update the branch sprites
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			float height = i * 150;

			if (branchPositions[i] == side::LEFT)
			{
				// Move the sprite to the left side;
				branches[i].setPosition(610, height);

				// flip the sprite round the other way
				branches[i].setRotation(180);
			} 
			else if(branchPositions[i] == side::RIGHT)
			{
				// Move the psrite to the right side;
				branches[i].setPosition(1330, height);
				//Set sprite rotaiton to normal
				branches[i].setRotation(0);
			}
			else
			{
				//Hide the branch
				branches[i].setPosition(3000, height);
			}
		}

		

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
		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		// Draw the tree
		window.draw(spriteTree);

		// Draw the player
		window.draw(spritePlayer);
		// Draw the axe
		window.draw(spriteAxe);
		// Draw the flying log
		window.draw(spriteLog);
		// Draw the gravestone
		window.draw(spriteRIP);

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

// Function definition
void updateBranches(int seed)
{
	//Move all the branches down one place;
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}


	// Spawn a new branch at position 0
	// LEFT, RIGHT or NON
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	case 2:
		branchPositions[0] = side::NONE;
		break;


	default:
		break;
	}
}

