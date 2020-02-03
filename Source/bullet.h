#pragma once
#include "Framework/Vector.h"
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/AudioManager.h"
class bullet : public GameObject
{
public:
	bullet();
	~bullet();

	void update(float dt);//Update Function
	void collisionResponse(GameObject * collider); //Collision for taking damage
};

