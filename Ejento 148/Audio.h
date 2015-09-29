#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>


class Audio {
public:
	void musicStart(std::string file, float volume = 10);

	void musicStop(char* file);

	void soundPlay(char* file);

private:


};