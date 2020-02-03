#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "Framework/TileMap.h"
#include "Framework/Collision.h"
#include "manageEnemies.h"
#include "manageBullets.h"


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState *state);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();
	std::vector<GameObject>* getBarriers() { return &barriers; };//Returns the vector of side barriers
	std::vector<GameObject>* getBarriers2() { return &barriers2;};//returns the vector of top barriers


private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager audio;

	//Views
	sf::View view1;//View for players position
	sf::View HUD;//view for HUD with players score

	//Level objects
	player Player;
	sf::Texture playerTexture;

	//Background and Level
	GameObject background;
	sf::Texture bgImage;
	GameObject ship;
	sf::Texture shipMap;

	//Tile Maps
	TileMap frontMap;
	TileMap boxMapLeft;
	TileMap boxMapRight;
	TileMap computerMap1;
	TileMap computerMap2;
	TileMap boxes3;
	TileMap computerMap3;

	manageEnemies Enemies;//Enemies in level
	manageBullets Bullets;//Bullets fired by player
	GameObject barrier;//Side barrier Game Object
	GameObject barrier2;//Top barrier Game Object
	GameObject portal;//Goal object
	std::vector<GameObject> barriers;//Vector of game object barrier
	std::vector<GameObject> barriers2;//Vector of game object barrier2
	sf::Font font;//Creates font object
	sf::Text score;//Creates text object for score
};