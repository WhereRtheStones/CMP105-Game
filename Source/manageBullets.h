#pragma once
#include "bullet.h"

class manageBullets : public GameObject
{
public:
	manageBullets();
	~manageBullets();

	void spawn();//Spawns bullets
	void update(float dt);//Updates bullets
	void deathCheck();//Checks status of bullet
	void render(sf::RenderWindow* window);//Renders bullet to screen
	void setTarget(sf::Vector2f vel);//Sets the speed of bullet as a vector
	void setSpawn(int x, int y);//Spawns bullets at specific coordinates

	std::vector <bullet> &getBullets();//Vector of bullets //Used for collision in level
private:
	AudioManager audio;//Audio for bullets
	std::vector <bullet> bullets;//Vector of bullets used in class
	sf::Texture sprite;
	int spawnx;//x coordinates of spawn according to players current position
	int spawny;//y coordinates of spawn according to players current position
	sf::Vector2f target;//The point where bullets will head //Set to mouse position in player class
	




};

