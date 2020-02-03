#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include <string>
#include <iostream>
class Instructions
{
public:
	Instructions(sf::RenderWindow* hwnd, Input* in, GameState *state);
	~Instructions();

	void handleInput(float dt);//Handles Input
	void update(float dt);//Update function
	void render();//Render function

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager audio;
	//Sprites for visual instructions
	GameObject alien;
	GameObject portal;
	sf::Texture Alien;
	sf::Texture Portal;
	//Text
	sf::Font font;
	sf::Text heading;
	sf::Text controls;
	sf::Text description;
	sf::Text goals;
};

