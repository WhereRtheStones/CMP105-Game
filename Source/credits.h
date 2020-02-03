#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include <string>
#include <iostream>
class credits
{
public:
	credits(sf::RenderWindow* hwnd, Input* in, GameState *state);
	~credits();

	void handleInput(float dt);//Input
	void update(float dt);//Update
	void render();//Rendering

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager audio;

	//Declares objects in state
	GameObject background;
	sf::Texture bg;

	sf::Font font;
	sf::Text winner;
	sf::Text me;
	sf::Text sounds;
	sf::Text sprites;
	sf::Text fonts;
};

