#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "player.h"
#include <string>
#include <iostream>
class gameOver
{
public:
	gameOver(sf::RenderWindow* hwnd, Input* in, GameState *state);
	~gameOver();

	void handleInput(float dt);//Input
	void update(float dt);//Update
	void render();//rendering

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager audio;
	GameObject goimage;
	sf::Texture bg;
	sf::Text text;
	sf::Font font;
};

