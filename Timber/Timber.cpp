#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
	// Create a video mode object VideoMode vm(1920, 1080)
	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Timber!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU Textur
	Texture textureBackground;

	//// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");
	/*if (!textureBackground.loadFromFile("graphics/background.png"))
	{
		std::cout << "Faild to load background image\n";
	}*/

	// Create a sprite
	Sprite spriteBackground;

	//// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	/// Set the spriteBackground to cover the screen spriteBackground.setPosition(0, 0);
	spriteBackground.setPosition(0, 0);

	while (window.isOpen())
	{
		/*
			Code here Handle the players input
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		******** Update the scene
		*/

		// Clear everything from the last frame window.clear();
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Show everything we just drew window.display();
		window.display();



	}

	return 0;
}