#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Laser.h"
#include "InvaderControl.h"
#include "Player.h"
#include "AnimationRenderer.h"
#include "Barrier.h"
#include "Level.h"
class Game
{
public:
	Game();
	void run();
	void GameOver(bool win, int score);

private:
	void handleEvent();//Unstucks window
	void changeText(Text& Box, const char* text, int value); // Change text of box by str(text + value)
	void nextLevelTransition();//Animation between levels
	int m_CurrentLevel = 1;

	sf::RenderWindow m_window;
	Text Score;
	Text Lifes;
};
