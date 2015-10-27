#ifndef _AUDIO_HPP
#define _AUDIO_HPP

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>


class Audio {
public:
	void MusicStart(std::string file, float volume);
	void MusicStop(char *file);
	void PlaySound(char *file);
private:
	sf::Music music;
};

#endif