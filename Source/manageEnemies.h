#pragma once
#include "enemy.h"

class manageEnemies
{
public:
	manageEnemies();
	~manageEnemies();
	void spawn();//Spawns enemies
	void update(float dt);//Updates enemies
	void deathCheck();//Checks if enemy is still alive
	void render(sf::RenderWindow* window);//Render enemies on window

	std::vector <enemy> &getEnemies();//Vector of enemy class Used in level for collision
protected:
	std::vector <enemy> enemies;//Vector of enemy used in manager class
	sf::Texture sprite;//Texture
	
	
};

