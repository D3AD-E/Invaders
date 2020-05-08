#include "Game.h"
#include <sstream>

Game::Game()
	: m_window({ 1180, 900 }, "Space Invaders")
	, Score("", RHolder::get().fonts.get("arcade"), 40)
	, Lifes("", RHolder::get().fonts.get("arcade"), 40)
{
	m_window.setPosition({ m_window.getPosition().x, 0 });
	m_window.setFramerateLimit(60);

	Score.setPosition({ 40,20 });
	Lifes.setPosition({ 960, 20 });
}

//Runs the main loop
void Game::run()
{
	Level* level = new Level(0.45f);
	//Main loop of the game
	while (m_window.isOpen()) {
		changeText(Lifes, "Lifes ", level->getLives());
		changeText(Score, "Score ", level->getScore());

		int outcome = level->run();
		if (outcome == 0)
		{
			GameOver(false, level->getScore());
			return;
		}
		else if (outcome == 1)
		{
			//Render
			m_window.clear();
			level->draw(m_window);
			m_window.draw(Lifes);
			m_window.draw(Score);
			m_window.display();
		}
		else if (outcome == 2)
		{
			nextLevelTransition();
			int temp = level->getScore();
			delete level;
			if (m_CurrentLevel == 2)
				level = new Level(0.35f, temp);
			else if (m_CurrentLevel == 3)
				level = new Level(0.30f, temp);
			else if (m_CurrentLevel == 4)
			{
				GameOver(true, temp);
				return;
			}
		}
		else if (outcome == 3)
		{
			GameOver(true, level->getScore());
			return;
		}
		//Handle window events
		handleEvent();
	}
}

void Game::GameOver(bool win, int score)
{
	m_window.clear();
	changeText(Score, "Final score  ", score);
	Score.setPosition({ 400,450 });
	if (!win)
		Lifes.setString("GAME OVER");
	else
		Lifes.setString("YOU WIN");
	Lifes.setCharacterSize(100);
	Lifes.setPosition({ 360,200 });
	m_window.draw(Score);
	m_window.draw(Lifes);
	m_window.display();
}

//Handles window events, called every frame
void Game::handleEvent()
{
	sf::Event e;

	while (m_window.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			m_window.close();
			break;

		default:
			break;
		}
	}
}

void Game::changeText(Text& Box, const char* text, int value)
{
	std::stringstream temp;
	temp << text << value;
	Box.setString(temp.str());
}

void Game::nextLevelTransition()
{
	m_CurrentLevel++;
	m_window.clear();
	Score.setString("Press  enter  to  go  to  the  next  level");
	Score.setPosition({ 220,380 });
	m_window.draw(Score);
	m_window.display();
	while (!Keyboard::isKeyPressed(Keyboard::Enter));
	Score.setPosition({ 40,20 });
}