#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Vector.h"
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "manageBullets.h"
#include <iostream>
class player : public GameObject
{
public:
	player();
	~player();
	void setPlayerWindowPos(sf::RenderWindow* win);//Passes pointer to window
	void setGunFire(manageBullets* gf);//Passes pointer to managebullets
	void handleInput(float dt);//Input synced with delta time
	void update(float dt);//Update synced with delta time
	void collisionResponse(GameObject * collider);//Passes pointer to colliding object
	void increaseScore();//Increases players score
	int getScore();//Returns player score
private:
	int score;//Players score
	Animation move_cycle;//Animation of player movement
	manageBullets* Bullets;//Pointer to bullet manager
	sf::RenderWindow* window;//Pointer to window
};