#ifndef _AUDIO_HPP
#define _AUDIO_HPP

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>


class Audio {
public:
	static void PlayMusic(std::string, float, bool);
	static void StopMusic();
	static void PlaySound(std::string, float, bool);
private:
	static sf::Music backgroundMusic;
	static sf::SoundBuffer buffer;
	static sf::Sound actionSound;
};

#endif