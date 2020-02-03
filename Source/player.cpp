#include "player.h"

player::player()
{
	//Animation frames
	move_cycle.addFrame(sf::IntRect(0, 0, 280,260));
	move_cycle.addFrame(sf::IntRect(322, 0, 300, 260));
	move_cycle.setFrameSpeed(1.f / 10.f);
	//Sets score to 0 upon construction
	score = 0;

}


player::~player()
{
}

void player::setPlayerWindowPos(sf::RenderWindow * win)
{
	window = win;//Sets pointer to refernced window input into function in level
}

void player::setGunFire(manageBullets * gf)
{
	Bullets = gf;//Sets pointer to referenced object
}

void player::handleInput(float dt)
{
	//Movement
	if (input->isKeyDown(sf::Keyboard::A))
	{
		velocity.x = -500;
	}
	else if (input->isKeyDown(sf::Keyboard::D))
	{
		velocity.x = 500;
	}
	else if (input->isKeyDown(sf::Keyboard::W))
	{
		velocity.y = -500;
	}
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		velocity.y = 500;
	}
	else
	{
		velocity.x = 0;//Resets velocity to 0 if no keys are pressed
		velocity.y = 0;
	}

	  /////////////////////
	//Space-bar is pressed//
	 /////////////////////

	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		//Sets bullet to travel towards mouse position
		int cursorX = input->getMouseX();//Gets mouse coordinates on window
		int cursorY = input->getMouseY();
		sf::Vector2f playerPos = static_cast<sf::Vector2f>(window->getSize());//Gets centre of window //Changes values to floats
		//This will ensure distance between player and mouse are consistent as view changes
		//View centre will be set to players position
		sf::Vector2f cursour(cursorX, cursorY);//Vector of floats with cursor position
		sf::Vector2f target = cursour-(playerPos/2.f);//Velocity of bullet based on the distance between player and cursor
		Bullets->setTarget(target);//Sets velocity of bullet to calculated distance
		Bullets->setSpawn(getPosition().x,getPosition().y);//Bullets spawn where player is currently positioned
		Bullets->spawn();//Spawns bullets
	}
}

void player::update(float dt)
{
	move(velocity*dt);//Moves player with delta time
	setTextureRect(move_cycle.getCurrentFrame());//Initialises animation

	//Stops player from exceeding specific boundaries
	if (getPosition().y < 1093)//if player is located in top part of ship
	{
		if (getPosition().x < 339)
		{
			setPosition(339, getPosition().y);
		}

		if (getPosition().x > 1100)
		{
			setPosition(1100, getPosition().y);
		}
	}

	if (getPosition().x < 339)//if player is in middle section
	{
		if (getPosition().y < 1082)
		{
			setPosition(getPosition().x, 1082);
		}
	}

	if (getPosition().x > 1100)//If player is in bottom part of ship
	{
		if (getPosition().y < 1092)
		{
			setPosition(getPosition().x, 1092);
		}
	}

	if (getPosition().x < 145)
	{
		setPosition(145, getPosition().y);
	}
	if (getPosition().x > 1294)
	{
		setPosition(1294, getPosition().y);
	}
	if (getPosition().y > 2513)
	{
		setPosition(getPosition().x, 2513);
	}
	  /////////
	//Animation//
	 //////////

	//Animation only occurs if player is on the move
	if (velocity.x > 0.0)
	{
		move_cycle.animate(dt);
		setTextureRect(move_cycle.getCurrentFrame());
	}
	else if (velocity.x < 0.0)
	{
		move_cycle.animate(dt);
		setTextureRect(move_cycle.getCurrentFrame());
	}
	else if (velocity.y > 0.0)
	{
		move_cycle.animate(dt);
		setTextureRect(move_cycle.getCurrentFrame());
	}
	else if (velocity.y < 0.0)
	{
		move_cycle.animate(dt);
		setTextureRect(move_cycle.getCurrentFrame());
	}

	else
	{
		move_cycle.reset();//Resets animation if no movement occurs
		setTextureRect(move_cycle.getCurrentFrame());
	}

	int cursorX = input->getMouseX();//Mouse coordinates
	int cursorY = input->getMouseY();

	sf::Vector2f playerPos = static_cast<sf::Vector2f>(window->getSize());//Gets centre of window
	//This will ensure player position stays consistent as view changes
	float y = (cursorY-(playerPos.y/2.f));//Distance between player and cursor on y axis
	float x = (cursorX - (playerPos.x)/2.f);//Distance between player and cursor on x axis
	float angle = ((atan2(y, x)) * (180 / 3.14159265));//Calculates angle of player and cursor distance
	setRotation(angle);//Rotates player based on this angle
}

void player::collisionResponse(GameObject * collider)
{
	float playerX = getPosition().x;//Centre of Player x coords. Origin is centred in level
	float playerY = getPosition().y;//Centre of Player y coords. Origin is centred in level
	float colX = collider->getPosition().x + (collider->getSize().x /2);//Centre of collider x axis
	float colY = collider->getPosition().y + (collider->getSize().y /2);//Centre of collider y axis

	float diffx = (abs(colX - playerX));//Distance between centres of colliders and player X axis
	float diffy = (abs(colY - playerY));//Distance between centres of colliders and player Y axis



	if (abs(diffx) > abs(diffy))//Identifies if player is closer to x or y centre
	{
		if (colX > playerX)//Right Hand of player collision
		{
			velocity.x = 0;
			setPosition(abs(colX - getSize().x), getPosition().y);//Moves player away from collider
		}
		if (colX < playerX)//Right Hand of player collision
		{
			velocity.x = 0;
			setPosition(abs(colX + getSize().x), getPosition().y);//Moves player away from collider
		}
	}
	else 
	{
		if (colY > playerY)//Below Player Collision
		{
			velocity.y = 0;
			setPosition(getPosition().x, abs(colY - getSize().y));//Moves player away from collider
		}
		else if (colY < playerY)//Above Player Collision
		{
			velocity.y = 0;
			setPosition(getPosition().x, abs(colY + getSize().y));//Moves player away from collider
		}
	}


}

void player::increaseScore()
{
	score= score + 10;//Increases score
}

int player::getScore()
{
	return score;//Returns score
}
