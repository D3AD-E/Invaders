#include "RHolder.h"

RHolder& RHolder::get()
{
	static RHolder holder;
	return holder;
}

RHolder::RHolder()
	: fonts("fonts", "ttf")
	, textures("Textures", "png")
	, soundBuffers("sfx", "ogg")
{
}