#include "Menu.h"



Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState *state)
{
	window = hwnd;
	input = in;
	gameState = state;

	//Background
	bgImage.loadFromFile("gfx/menusprite.png");
	bg.setSize(sf::Vector2f(1200, 700));
	bg.setPosition(0, 0);
	bg.setTexture(&bgImage);

	//Text
	if (!font.loadFromFile("font/zrnic rg.ttf"))
	{
		std::cout << "Error loading font/n";
	}
	text.setFont(font);
	text.setString("ESCAPE THE SHIP!");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 69, 0));
	text.setPosition(300, 0);

	text2.setFont(font);
	text2.setString("PRESS ENTER");
	text2.setCharacterSize(50);
	text2.setFillColor(sf::Color(255, 69, 0));
	text2.setPosition(300, 200);
}

Menu::~Menu()
{
}

void Menu::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		input->setKeyUp(sf::Keyboard::Enter);
		gameState->setCurrentState(State::INSTRUCTIONS);//Changes state on key press 
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);//Closes window
		window->close();
	}
}

void Menu::update(float dt)
{

}

void Menu::render()
{
	beginDraw();
	window->draw(bg);
	window->draw(text);
	window->draw(text2);
	endDraw();
}
//Begins rendering
void Menu::beginDraw()
{
	window->clear(sf::Color::Black);
}
//Ends rendering
void Menu::endDraw()
{
	window->display();
}
