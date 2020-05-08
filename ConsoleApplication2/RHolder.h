#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "RManager.h"

class RHolder
{
private:
	RHolder();

public:
	static RHolder& get();

	RManager<sf::Font>           fonts;
	RManager<sf::Texture>        textures;
	RManager<sf::SoundBuffer>    soundBuffers;
};
