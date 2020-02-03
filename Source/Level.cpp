#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState *state)
{
	window = hwnd;
	input = in;
	gameState = state; //Takes in current state to allow for changes of state
	view1.reset(sf::FloatRect(360.f, 0.f, 1200.f, 800.f));//Sets window view of the level
	HUD.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));//Creates heads up display


	// initialise game objects

	//Background
	bgImage.loadFromFile("gfx/spacebg.png");
	background.setSize(sf::Vector2f(2160*2, 3840*2));
	background.setPosition(-1440, -2560);
	background.setTexture(&bgImage);

	//Ship
	//Loads image to create the setting for main gameplay
	//Tile Maps are a seperate entity
	shipMap.loadFromFile("gfx/Ship Map1.png");
	ship.setSize(sf::Vector2f(1440, 2560));
	ship.setPosition(0, 0);
	ship.setTexture(&shipMap);

	//Score
	if (!font.loadFromFile("font/zrnic rg.ttf"))//Sets font for use
	{
		std::cout << "Error loading font/n";
	}
	//Defines score properties
	score.setFont(font);
	score.setCharacterSize(100);
	score.setPosition(0, 0);
	score.setFillColor(sf::Color::Black);

	//Player Sprite 
	playerTexture.loadFromFile("gfx/Space_Marine.png");
	Player.setInput(input);//Passes input through to player class
	Player.setTexture(&playerTexture);
	Player.setGunFire(&Bullets);//Passes reference of bullet manager through to player class //Used for firing bullets
	Player.setPlayerWindowPos(window);//Passes window object through to player class //Used to synchronised mouse coords to players view
	Player.setAlive(true);
	Player.setSize(sf::Vector2f(120, 120));
	Player.setOrigin(60, 60);//Sets the origin for player object to centre to allow for accurate rotation
	Player.setCollisionBox(0, 0, 100, 100);
	Player.setCollider(true);
	Player.setPosition(700, 400);

	//Enemy Spawns
	for (int i = 0; i < 40; i++)
	{
		Enemies.spawn();//Spawns enemies through function within class that has set all needed variables
	}

	//Portal
	//Blank Collision Box at certain position which ends the game
	portal.setPosition(656, 2358);
	portal.setSize(sf::Vector2f(0,0));
	portal.setCollisionBox(0,0,128, 148);

	//Barriers

	//Defines properties of side barriers
	//Blank Collision Boxes
	for (int i = 0; i < 4; i++)
	{
		barrier.setSize(sf::Vector2f(0, 0));
		barrier.setCollisionBox(0, 0, 12, 864);
		barrier.setCollider(true);
		barriers.push_back(barrier);
	};
	//Sets position for each barrier
	barriers[0].setPosition(sf::Vector2f(328,230));
	barriers[1].setPosition(sf::Vector2f(1102,232));
	barriers[2].setPosition(sf::Vector2f(134,1094));
	barriers[3].setPosition(sf::Vector2f(1294,1094));

	//Defines properties of top barriers
	//Blank Collision Boxes
	for (int i = 0; i < 4; i++)
	{
		barrier2.setSize(sf::Vector2f(0, 0));
		barrier2.setCollisionBox(0, 0, 182, 12);
		barrier2.setCollider(true);
		barriers2.push_back(barrier2);
	}
	//Sets position for each barrier
	barriers2[0].setPosition(sf::Vector2f(146,1082));
	barriers2[1].setPosition(sf::Vector2f(1114,1082));
	barriers2[2].setPosition(sf::Vector2f(146,1950));
	barriers2[3].setPosition(sf::Vector2f(1114,1950));

	//Loads textures for tile maps
	frontMap.loadTexture("gfx/Ship Map1.png");
	boxMapLeft.loadTexture("gfx/Ship Map1.png");
	boxMapRight.loadTexture("gfx/Ship Map1.png");
	computerMap1.loadTexture("gfx/Ship Map1.png");
	computerMap2.loadTexture("gfx/Ship Map1.png");
	boxes3.loadTexture("gfx/Ship Map1.png");
	computerMap3.loadTexture("gfx/Ship Map1.png");

	//Sets properties for tiles
	GameObject tile;
	std::vector<GameObject> tiles;
	for (int i = 0; i < 15; i++)
	{
		tile.setSize(sf::Vector2f(64, 64));
		tile.setCollisionBox(0, 0, 64, 64);
		tile.setCollider(true);
		tiles.push_back(tile);
	};

	//Declares which part of image is rendered for each tile
	tiles[0].setCollider(false);
	tiles[0].setTextureRect(sf::IntRect(1408, 2528, 64, 64));//Blank

	tiles[1].setTextureRect(sf::IntRect(340, 176, 192, 64));
	tiles[1].setSize(sf::Vector2f(192, 64));//Front of Ship Top Left
	tiles[1].setCollisionBox(0, 0, 192, 64);


	tiles[2].setTextureRect(sf::IntRect(532, 240, 320, 64));
	tiles[2].setSize(sf::Vector2f(320, 64));//Front of Ship Middle
	tiles[2].setCollisionBox(0, 0, 320, 64);


	tiles[3].setTextureRect(sf::IntRect(852, 176, 256, 64));
	tiles[3].setSize(sf::Vector2f(256, 64));//Front of Ship Top Right
	tiles[2].setCollisionBox(0, 0, 256, 64);


	tiles[4].setTextureRect(sf::IntRect(342, 774, 64, 64));//Red Box

	tiles[5].setTextureRect(sf::IntRect(212, 1108, 64, 64));//Green Box

	tiles[6].setTextureRect(sf::IntRect(342, 960, 64, 64));//Console 1

	tiles[7].setTextureRect(sf::IntRect(406, 960, 64, 64));//Console 1

	tiles[8].setTextureRect(sf::IntRect(470, 960, 64, 64));//Console 1

	tiles[9].setTextureRect(sf::IntRect(594, 1136, 64, 64));//Console 2
	tiles[10].setTextureRect(sf::IntRect(658, 1136, 64, 64));//Console 2

	tiles[11].setTextureRect(sf::IntRect(546, 1610, 64, 64));//Console 3

	tiles[12].setTextureRect(sf::IntRect(546, 1674, 64, 64));//Console 3

	tiles[13].setTextureRect(sf::IntRect(866, 1610, 64, 64));//Console 3

	tiles[14].setTextureRect(sf::IntRect(866, 1674, 64, 64));//Console 3

	//Vectors for setting position of each tile

//Front
frontMap.setTileSet(tiles);//Sets tiles
// Map dimensions
sf::Vector2u mapSize1(9, 2);
// build map
std::vector<int> map1 = {
	1,0,0,0,0,0,0,0,3,
	0,0,0,2,0,0,0,0,0
};
frontMap.setTileMap(map1, mapSize1);
frontMap.setPosition(sf::Vector2f(340, 176));
frontMap.buildLevel();

//Boxes 1
boxMapLeft.setTileSet(tiles);//Sets tiles
// Map dimensions
sf::Vector2u boxSize(4, 2);
// build map
std::vector<int> boxMap = {
	4,4,4,4,
	4,4,4,4
};
boxMapLeft.setTileMap(boxMap, boxSize);
boxMapLeft.setPosition(sf::Vector2f(342, 774));
boxMapLeft.buildLevel();

//Boxes 2
//Uses the same vector as the previous tile map just in a different position
boxMapRight.setTileSet(tiles);//Sets tiles
boxMapRight.setTileMap(boxMap, boxSize);
boxMapRight.setPosition(sf::Vector2f(844, 774));
boxMapRight.buildLevel();

//Computer 1
computerMap1.setTileSet(tiles);//Sets tiles
// Map dimensions
sf::Vector2u cmpSize1(3, 1);
// build map
std::vector<int> cmpMap1 = {
	6,7,8
};
computerMap1.setTileMap(cmpMap1, cmpSize1);
computerMap1.setPosition(sf::Vector2f(342, 960));
computerMap1.buildLevel();

//Computer 2
computerMap2.setTileSet(tiles);//Sets tiles
// Map dimensions
sf::Vector2u cmpSize2(4, 1);
// build map
std::vector<int> cmpMap2 = {
	9,10,9,10
};
computerMap2.setTileMap(cmpMap2, cmpSize2);
computerMap2.setPosition(sf::Vector2f(594, 1136));
computerMap2.buildLevel();


//Boxes 3
boxes3.setTileSet(tiles);//Sets tiles
// Map dimensions
sf::Vector2u boxSize3(11, 1);
// build map
std::vector<int> boxMap3 = {
	4,5,4,5,4,5,4,5,4,5,4
};
boxes3.setTileMap(boxMap3, boxSize3);
boxes3.setPosition(sf::Vector2f(540, 1356));
boxes3.buildLevel();

//Computer 3
computerMap3.setTileSet(tiles);//Sets tiles
// Map dimensions
sf::Vector2u cmpSize3(11, 2);
// build map
std::vector<int> cmpMap3 = {
	5,5,5,5,5,11,9,10,9,10,13,
	0,0,0,0,0,12,0,0,0,0,14
};
computerMap3.setTileMap(cmpMap3, cmpSize3);
computerMap3.setPosition(sf::Vector2f(226, 1610));
computerMap3.buildLevel();

//Audio
audio.addMusic("sfx/BO2.ogg", "leveltheme");//Main Game music added to level
audio.getMusic()->setVolume(100);//Increases volume
audio.addSound("sfx/0477.ogg", "wilhelm");//Player death sound
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	Player.handleInput(dt);//Handles Input for player

	//Pause function
	//Pause Gamestate uses levels input and rendering
	if (input->isKeyDown(sf::Keyboard::P))
	{
		//Pauses Game
		if (gameState->getCurrentState() != State::PAUSE) //Checks current state
		{
			input->setKeyUp(sf::Keyboard::P);
			gameState->setCurrentState(State::PAUSE);//Changes to pause state
		}
		else
		{
			input->setKeyUp(sf::Keyboard::P);
			gameState->setCurrentState(State::LEVEL);//Unpauses game
		}
	}
	
	//Closes window
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}
}

// Update game objects
void Level::update(float dt)
{
	//Music

	if (audio.getMusic()->getStatus() == sf::SoundSource::Stopped)//Checks if music is stopped
	{
		audio.playMusicbyName("leveltheme");//Plays level theme if no other music is playing
	}

	//Score
	std::string points = std::to_string(Player.getScore());//Recieves players score from player class //Converted to string
	score.setString(points);//Converted String object is set as string

	//Update functions for used classes
	Player.update(dt);
	Enemies.update(dt);
	Bullets.update(dt);

	//View 
	view1.setCenter(Player.getPosition().x, Player.getPosition().y);//Sets the centre of the view to where the player is located
	//Changes as player moves through the level

	//Player Death
	if (!Player.isAlive())
	{
		audio.stopAllMusic();//Stops music
		gameState->setCurrentState(State::GAMEOVER);//Changes current state
	}
	  //////////
	//Collision//
	///////////

	//Player and enemies
	for (int i = 0; i < Enemies.getEnemies().size(); i++)//Recieves enemy class from manager //Specifies which enemy has collided
	{
		if (Enemies.getEnemies().at(i).isCollider())//Only Collides if enemy is a collider
		{
			if (Collision::checkBoundingBox(&Enemies.getEnemies().at(i), &Player))
			{
				audio.playSoundbyName("wilhelm");//Player Death Sound
				Player.setAlive(false);//Kills player
			}
		}
	}

	//Player and Portal
	if (Collision::checkBoundingBox(&Player, &portal))
	{
		audio.stopAllMusic();//Stops music
		gameState->setCurrentState(State::CREDITS);//Player has won //Change state
	}

	//Level Object Collision for Player, Enemies and bullets

	//Collision for side barriers
	std::vector<GameObject>* sides = getBarriers();//Creates vector from calling function
	for (int i = 0; i < sides->size(); i++)
	{
		if ((*sides)[i].isCollider())//Checks if sides are colliders
		{ //Barriers and Enemies
			for (int j = 0; j < Enemies.getEnemies().size(); j++)//Vector of enemies
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*sides)[i]))//Checks bounding Boxes
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes velocity/direction
				}
			}
			//Bullets and barriers
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{ //Bullets and barriers
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*sides)[i]))//Checks bounding boxes
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);//Calls collision response
				}
			}
		}
	}

	//Collision for top barriers
	std::vector<GameObject>* tops = getBarriers2();//Creates vector from calling function
	for (int i = 0; i < tops->size(); i++)
	{
		if ((*tops)[i].isCollider()) //Checks if collider is true
		{
			for (int j = 0; j < Enemies.getEnemies().size(); j++)//Barriers and enemies
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*tops)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes velocity/Direction
				}

				for (int k = 0; k < Bullets.getBullets().size(); k++)
				{
					if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*tops)[i]))
					{
						Bullets.getBullets().at(k).collisionResponse(NULL);//Calls collision response
					}
				}
			}
		}
	}
	  //////////////////
	//TileMap Collision//
	  /////////////////

	//Front of ship collision
	std::vector<GameObject>* front = frontMap.getLevel();
	for (int i = 0; i < (int)front->size(); i++)
	{
		if ((*front)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*front)[i]))
			{
				Player.collisionResponse(&(*front)[i]);//Player Collision Response
			}
			for (int j = 0; j < Enemies.getEnemies().size(); j++)
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*front)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
				}
			}
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*front)[i]))
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);//Collision Response
				}
			}
		}
	}

	//Left Box Collision
	std::vector<GameObject>* lBox = boxMapLeft.getLevel();
	for (int i = 0; i < (int)lBox->size(); i++)
	{
		if ((*lBox)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*lBox)[i]))
			{
				Player.collisionResponse(&(*lBox)[i]);//Player Collision Response
			}
			for (int j = 0; j < Enemies.getEnemies().size(); j++)
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*lBox)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
				}
			}
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*lBox)[i]))
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);
				}
			}
		}
	}

	//Right Box Collision
	std::vector<GameObject>* rBox = boxMapRight.getLevel();
	for (int i = 0; i < (int)rBox->size(); i++)
	{
		if ((*rBox)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*rBox)[i]))
			{
				Player.collisionResponse(&(*rBox)[i]);//Player Collision Response
			}
			for (int j = 0; j < Enemies.getEnemies().size(); j++)
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*rBox)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
				}
			}
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*rBox)[i]))
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);
				}
			}
		}
	}

	//Computer 1 Collision
	std::vector<GameObject>* cmp1 = computerMap1.getLevel();
	for (int i = 0; i < (int)cmp1->size(); i++)
	{
		if ((*cmp1)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*cmp1)[i]))
			{
				Player.collisionResponse(&(*cmp1)[i]);//Player Collision Response
			}
			for (int j = 0; j < Enemies.getEnemies().size(); j++)
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*cmp1)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
				}
			}
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*cmp1)[i]))
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);
				}
			}
		}
	}

	//Computer 2 Collision
	std::vector<GameObject>* cmp2 = computerMap2.getLevel();
	for (int i = 0; i < (int)cmp2->size(); i++)
	{
		if ((*cmp2)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*cmp2)[i]))
			{
				Player.collisionResponse(&(*cmp2)[i]);//Player Collision Response
			}
			for (int j = 0; j < Enemies.getEnemies().size(); j++)
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*cmp2)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
				}
			}
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*cmp2)[i]))
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);
				}
			}
		}
	}

	//Boxes 3 Collision
	std::vector<GameObject>* box3 = boxes3.getLevel();
	for (int i = 0; i < (int)box3->size(); i++)
	{
		if ((*box3)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*box3)[i]))
			{
				Player.collisionResponse(&(*box3)[i]);//Player Collision Response
			}
			for (int j = 0; j < Enemies.getEnemies().size(); j++)
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*box3)[i]))
				{
					Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
				}
			}
			for (int k = 0; k < Bullets.getBullets().size(); k++)
			{
				if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*box3)[i]))
				{
					Bullets.getBullets().at(k).collisionResponse(NULL);
				}
			}
		}
	}

	//Computer 3 Collision
	std::vector<GameObject>* cmp3 = computerMap3.getLevel();
	for (int i = 0; i < (int)cmp3->size(); i++)
	{
		if ((*cmp3)[i].isCollider())//Checks if tilemap is a collider
		{
			if (Collision::checkBoundingBox(&Player, &(*cmp3)[i]))
			{
				Player.collisionResponse(&(*cmp3)[i]);//Player Collision Response
			}
		}
		for (int j = 0; j < Enemies.getEnemies().size(); j++)
		{
			if (Collision::checkBoundingBox(&Enemies.getEnemies().at(j), &(*cmp3)[i]))
			{
				Enemies.getEnemies().at(j).setVelocity(-Enemies.getEnemies().at(j).getVelocity());//Changes direction
			}
		}
		for (int k = 0; k < Bullets.getBullets().size(); k++)
		{
			if (Collision::checkBoundingBox(&Bullets.getBullets().at(k), &(*cmp3)[i]))
			{
				Bullets.getBullets().at(k).collisionResponse(NULL);
			}
		}
	}

	//Collision between bullets and enemy objects
	for (int i = 0; i < Enemies.getEnemies().size(); i++)//Vector of Enemies
	{
		for (int j = 0; j < Bullets.getBullets().size(); j++)//Vector of bullets
		{
			if (Bullets.getBullets().at(j).isCollider() && Enemies.getEnemies().at(i).isCollider())//Checks if both vectors are colliders
			{
				if (Collision::checkBoundingBox(&Enemies.getEnemies().at(i), &Bullets.getBullets().at(j)))
				{
					Bullets.getBullets().at(j).collisionResponse(NULL);//Collision Response
					Enemies.getEnemies().at(i).collisionResponse(NULL, 10);//Deals damage to enemy
 					Player.increaseScore();//Gives player more score for each succesful hit
				}
			}
		}
	}
	
}

// Render level
void Level::render()
{
	beginDraw();
	window->setView(view1);
	window->draw(background);
	window->draw(ship);
	frontMap.render(window);
	boxMapLeft.render(window);
	boxMapRight.render(window);
	computerMap1.render(window);
	computerMap2.render(window);
	computerMap3.render(window);
	boxes3.render(window);
	window->draw(Player);
	Enemies.render(window);
	Bullets.render(window);
	window->setView(HUD);//Declared after view 1 renders to only have score render as part of the HUD
	window->draw(score);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}