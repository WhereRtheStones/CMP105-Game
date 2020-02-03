#include "Instructions.h"



Instructions::Instructions(sf::RenderWindow* hwnd, Input* in, GameState *state)
{
	window = hwnd;
	input = in;
	gameState = state;

	//Render Text
	if (!font.loadFromFile("font/zrnic rg.ttf"))
	{
		std::cout << "Error loading font/n";
	}
	heading.setFont(font);
	heading.setString("INSTRUCTIONS:");
	heading.setCharacterSize(30);
	heading.setFillColor(sf::Color(255, 69, 0));
	heading.setPosition(hwnd->getSize().x/2-15, 0);

	controls.setFont(font);
	controls.setString(" Controls\n W\n A\n S\n D\n SPACE\n MOUSE");
	controls.setCharacterSize(50);
	controls.setFillColor(sf::Color(255, 69, 0));
	controls.setPosition(0, 150);

	description.setFont(font);
	description.setString(" \n Up\n Left\n Right\n Down\n Shoot\n ROTATE AND AIM");
	description.setCharacterSize(50);
	description.setFillColor(sf::Color(255, 69, 0));
	description.setPosition(200, 150);

	//Loads sprites for information
	Alien.loadFromFile("gfx/staticAlien.png");
	alien.setSize(sf::Vector2f(144, 104));
	alien.setPosition(400, 150);
	alien.setTexture(&Alien);

	Portal.loadFromFile("gfx/portal.png");
	portal.setSize(sf::Vector2f(64, 96));
	portal.setPosition(420, 250);//I swear the 420 is just a coincidence
	portal.setTexture(&Portal);

	goals.setFont(font);
	goals.setString("Goals\nAvoid/Kill For Points \n\nReach to win the game");
	goals.setCharacterSize(50);
	goals.setFillColor(sf::Color(255, 69, 0));
	goals.setPosition(550, 100);

	//Audio
	audio.addMusic("sfx/PM_AR_125_Fm_G.ogg", "menutheme");//Plays audio
	audio.playMusicbyName("menutheme");//Audio plays upon construction
	//This allows it to play across two state(Menu and Instructions) with restarting or interupting song
}


Instructions::~Instructions()
{
}

void Instructions::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		input->setKeyUp(sf::Keyboard::Enter);
		audio.stopAllMusic();//Stops music
		gameState->setCurrentState(State::LEVEL);//Changes State
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();//Closes window
	}
}

void Instructions::update(float dt)
{
}

void Instructions::render()
{
	beginDraw();
	window->draw(heading);
	window->draw(controls);
	window->draw(description);
	window->draw(alien);
	window->draw(portal);
	window->draw(goals);
	endDraw();
}

//Begins rendering
void Instructions::beginDraw()
{
	window->clear(sf::Color::Black);
}
//Ends rendering
void Instructions::endDraw()
{
	window->display();
}
