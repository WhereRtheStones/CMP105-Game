#include "manageEnemies.h"



manageEnemies::manageEnemies()
{
	sprite.loadFromFile("gfx/Alien_Enemy.png");//Loads sprite

	srand(time(0));//Syncs rand function with time
	  ////////////////
	//Enemy properties//
	  ////////////////

	for (int i = 0; i < 40; i++)//Initialises vector of enemies and sets properties //Dead by default
	{
		enemies.push_back(enemy());
		enemies[i].setAlive(false);
		enemies[i].setTexture(&sprite);
		enemies[i].setSize(sf::Vector2f(140, 100));
		enemies[i].setHealth(10);
		enemies[i].setCollisionBox(0, 0, 140, 100);
		enemies[i].setPosition(350 + (rand() % (900 - 350 + 1)), 460 + (rand() % (660 - 460 + 1)));
		enemies[i].setVelocity(300, 0);
	}
	for (int i = 0; i < 30; i++)//Changes properties for this set of enemies
	{
		enemies[i].setPosition(200, 1160);
		enemies[i].setVelocity(300, 100);
		enemies[i + 1].setVelocity(500, 0);
	}
	for (int i = 0; i < 28; i++)//Changes properties for this set of enemies
	{
		enemies[i].setPosition(1060, 1100);
		enemies[i].setVelocity(-300, 100);
		enemies[i + 1].setVelocity(-500, 0);
	}

	for (int i = 0; i < 24; i++)//Changes properties for this set of enemies
	{
		enemies[i].setPosition(200 + (rand() % (1100 - 200 + 1)),1430 + (rand() % (1500 - 1430 + 1)));
		enemies[i].setVelocity(700, 10);
	}

	
	for (int i = 0; i < 20; i++)//Changes properties for this set of enemies
	{
		enemies[i].setPosition(120 + (rand() % (1200 - 120 + 1)), 1962 + (rand() % (2400 - 1962 + 1)));
		enemies[i].setVelocity(3000, 0);
	}

}


manageEnemies::~manageEnemies()
{
}

void manageEnemies::spawn()
{
	for (int i = 0; i < enemies.size(); i++) //Spawns enemies on screen
	{
		if (!enemies[i].isAlive())
		{
			enemies[i].setAlive(true);
			enemies[i].setCollider(true);
			return;
		}
	}
}

void manageEnemies::update(float dt)
{
	for (int i = 0; i < enemies.size(); i++)//Updates enemies if they are alive
	{
		if (enemies[i].isAlive())
		{
			enemies[i].update(dt);
		}

	}
	deathCheck();//Runs death check
}

void manageEnemies::deathCheck()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			if (enemies[i].getHealth() <= 0)//Checks if enemy health is at or below zero
			{
				enemies[i].setCollider(false);//Sets collider false to stop collision of dead objects
				enemies[i].setAlive(false);//Enemy is set to dead when health is zero or less
			}
		}
	}
}

void manageEnemies::render(sf::RenderWindow * window)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			window->draw(enemies[i]);//Renders alive enemies to screen
		}
	}
}

std::vector<enemy>& manageEnemies::getEnemies()
{
	return enemies;//Returns enemy vector for use in level collision
}
