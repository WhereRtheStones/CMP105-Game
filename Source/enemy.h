#pragma once
#include "Framework/Vector.h"
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
class enemy : public GameObject
{
public:
	enemy();
	~enemy();

	void update(float dt);//Update
	void collisionResponse(GameObject * collider, int d); //Collision for taking damage
	void setHealth(int h);//Function for setting enemy health
	int getHealth();//Returns enemies health

private:
	int health;//Enemies health
	Animation move_cycle;//Animation
};

