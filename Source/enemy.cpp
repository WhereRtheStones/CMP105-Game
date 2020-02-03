#include "enemy.h"



enemy::enemy()
{
	//Sets animation frames
	move_cycle.addFrame(sf::IntRect(0, 0, 360, 260));
	move_cycle.addFrame(sf::IntRect(380, 0, 360, 260));
	move_cycle.setFrameSpeed(1.f / 20.f);
}


enemy::~enemy()
{
}

void enemy::update(float dt)
{
	move(velocity*dt);//Moves enemy based on delta time
	move_cycle.animate(dt);//Animates based on delta time;
	setTextureRect(move_cycle.getCurrentFrame());//Sets animatin frames
	
	//Changes direction upon reaching a specific point
	if (getPosition().x > 1200)
	{
		velocity = -velocity;
	}
	if (getPosition().x < 92)
	{
		velocity = -velocity;
	}
	
	if (velocity.x < 0)
	{
		move_cycle.setFlipped(true);//Flips sprite if heading to the left
	}
	else
	{
		move_cycle.setFlipped(false);//Flips sprite if heading to the right
	}
}

void enemy::collisionResponse(GameObject * collider,int d)
{
	setHealth(getHealth()-d);//Enemy takes damage when hit
}

void enemy::setHealth(int h)
{
	health = h;//Sets health
}


int enemy::getHealth()
{
	return health;//Returns health
}

