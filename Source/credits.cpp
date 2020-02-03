#include "credits.h"



credits::credits(sf::RenderWindow* hwnd, Input* in, GameState *state)
{
	window = hwnd;
	input = in;
	gameState = state;

	//Background
	bg.loadFromFile("gfx/spacebg.png");
	background.setSize(sf::Vector2f(3840,2160));
	background.setPosition(-1280,-720);
	background.setTexture(&bg);

	//Renders text
	if (!font.loadFromFile("font/zrnic rg.ttf"))
	{
		std::cout << "Error loading font/n";
	}
	winner.setFont(font);
	winner.setString("YOU WIN!\nYOU ROCK!");
	winner.setCharacterSize(100);
	winner.setFillColor(sf::Color(255, 69, 0));
	winner.setPosition(300, 0);

	me.setFont(font);
	me.setString("Game programmed by Jack Edgar \n1800575");
	me.setCharacterSize(30);
	me.setFillColor(sf::Color(255, 69, 0));
	me.setPosition(300, 210);

	sprites.setFont(font);
	sprites.setString("Sprites Used \nPlayer Sprite-'RageWortt',https://ragewortt.itch.io/sci-fi-armored-soldiers \nAlien Sprite-'RageWortt',https://ragewortt.itch.io/sci-fi-armored-soldiers \nShip Background and Tileset-'Viktor', https://v-ktor.itch.io/32x32-rpg-tilesets \nSpace Background-'Wallpaperplay', https://wallpaperplay.com/board/blue-space-wallpapers");
	sprites.setCharacterSize(20);
	sprites.setFillColor(sf::Color::Black);
	sprites.setPosition(0,300);

	sounds.setFont(font);
	sounds.setString("Sounds Used\n Level Music-'Call of Duty:Black Ops 2, Activision, Treyarch'\nMenu Music-'Phil Michalski',https://www.pmsfx.com/free \n Laser Sfx-'PMSFX',https://www.pmsfx.com/free \nPlayer Death Sound - 'Wilhelm Scream', https://bigsoundbank.com/detail-0477-wilhelm-scream.html");
	sounds.setCharacterSize(20);
	sounds.setFillColor(sf::Color::Black);
	sounds.setPosition(0, 500);

	fonts.setFont(font);
	fonts.setString("Fonts Used\n'zrnic_rg'-'TypoDermic Fonts', https://www.dafont.com/zrnic.font");
	fonts.setCharacterSize(20);
	fonts.setFillColor(sf::Color::Black);
	fonts.setPosition(500, 500);

	audio.addMusic("sfx/PM_AR_125_Fm_D.ogg", "credits");//Adds music
}


credits::~credits()
{
}

void credits::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		window->close();
	}
}

void credits::update(float dt)
{
	if (audio.getMusic()->getStatus() == sf::SoundSource::Stopped)
	{
		audio.playMusicbyName("credits");//Plays music if no other music is playing
	}
}

void credits::render()
{
	beginDraw();
	window->draw(background);
	window->draw(winner);
	window->draw(me);
	window->draw(sounds);
	window->draw(sprites);
	window->draw(fonts);
	endDraw();
}

void credits::beginDraw()
{
	window->clear(sf::Color::Black);
}

void credits::endDraw()
{
	window->display();
}
