#include "bullet.h"



bullet::bullet()
{
}


bullet::~bullet()
{
}

void bullet::update(float dt)
{
	move(velocity*dt);//Moves based on velocity
}

void bullet::collisionResponse(GameObject * collider)
{
	setCollider(false);//Sets collider to false if collided // Stops further collision with other objects
	setAlive(false);//Sets bullet to dead
}
