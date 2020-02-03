#include "manageBullets.h"



manageBullets::manageBullets()
{
	sprite.loadFromFile("gfx/Beam.png");//Loads sprite
	audio.addSound("sfx/PM_AG_7_3_ABSTRACT_GUNS.ogg","laser");//Adds sound of laser shot

	//Sets bullets properties
	for (int i = 0; i < 50; i++)
	{
		bullets.push_back(bullet());
		bullets[i].setAlive(false);
		bullets[i].setTexture(&sprite);
		bullets[i].setSize(sf::Vector2f(45, 45));
		bullets[i].setCollisionBox(0, 0, 45, 45);
		bullets[i].setCollider(false);
	}

}


manageBullets::~manageBullets()
{
}

void manageBullets::spawn()
{
	for (int i = 0; i < bullets.size(); i++)//Spawns bullets
	{
		if (!bullets[i].isAlive())
		{
			bullets[i].setAlive(true);
			bullets[i].setPosition(spawnx, spawny);//Spawn point set recieved from player class
			bullets[i].setVelocity(target);//Sets velocity to the position of target
			bullets[i].setCollider(true);
			audio.playSoundbyName("laser");//Plays sound when shot
			return;
		}
	}
}

void manageBullets::update(float dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].update(dt);
		}
	}
	deathCheck();
}

void manageBullets::deathCheck()
{
	//Kills any bullet going out of bounds
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			if (bullets[i].getPosition().x < 0)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().x > 1440)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < 0)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > 2560)
			{
				bullets[i].setAlive(false);
			}
		}
	}
}

void manageBullets::render(sf::RenderWindow * window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);//Draws bullet
		}
	}
}

void manageBullets::setTarget(sf::Vector2f vel)
{
	target = vel;//Target is bullet velocity as vector based on targeted position
}

void manageBullets::setSpawn(int x, int y)
{
	spawnx = x;//Sets spawns
	spawny = y;
}

std::vector<bullet>& manageBullets::getBullets()
{
	return bullets;//Returns bullet game object for collision in level
}
