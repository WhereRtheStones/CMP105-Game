#include "gameOver.h"

gameOver::gameOver(sf::RenderWindow * hwnd, Input * in, GameState * state)
{
	window = hwnd;
	input = in;
	gameState = state;

	//Renders Text
	if (!font.loadFromFile("font/zrnic rg.ttf"))
	{
		std::cout << "Error loading font/n";
	}
	text.setFont(font);
	text.setString("Press Enter to exit");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Red);
	text.setPosition(700,500);

	//Background
	bg.loadFromFile("gfx/gameover.png");
	goimage.setSize(sf::Vector2f(1000, 800));
	goimage.setPosition(0, 0);
	goimage.setTexture(&bg);

	//Adds audio
	audio.addMusic("sfx/PM_AR_125_Fm_G.ogg", "menutheme");
}

gameOver::~gameOver()
{

}

void gameOver::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Enter))
	{
		input->setKeyUp(sf::Keyboard::Enter);
		window->close();//Close Window
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}
}

void gameOver::update(float dt)
{
	if (audio.getMusic()->getStatus() == sf::SoundSource::Stopped)
	{
		audio.playMusicbyName("menutheme");//Plays music if no other music is playing
	}
}

//Renders objects
void gameOver::render()
{
	beginDraw();
	window->draw(text);
	window->draw(goimage);
	endDraw();
}

void gameOver::beginDraw()
{
	window->clear(sf::Color::Black);
}

void gameOver::endDraw()
{
	window->display();

}
