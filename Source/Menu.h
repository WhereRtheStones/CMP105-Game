#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include <string>
#include <iostream>
class Menu
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameState *state);
	~Menu();

	void handleInput(float dt);//Input
	void update(float dt);//Update function
	void render();//Renders game objects

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager audio;
	GameObject bg;
	sf::Texture bgImage;
	sf::Font font;
	sf::Text text;
	sf::Text text2;
};

