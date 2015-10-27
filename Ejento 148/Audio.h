#ifndef _AUDIO_HPP
#define _AUDIO_HPP

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>


class Audio {
public:
	void PlayAudio(std::string, float, bool);
	void StopAudio();
private:
	sf::Music music;
};

#endif