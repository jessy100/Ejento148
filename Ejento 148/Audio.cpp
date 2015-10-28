#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Audio.h"
#include <string>
#include <iostream>

void Audio::PlayMusic(std::string file, float volume, bool loop){
	if (!backgroundMusic.openFromFile("resources/audio/"+file)) {
		std::cout << "ERROR Music file " << file << " not found\n";
	}
	backgroundMusic.setLoop(loop);
	backgroundMusic.setVolume(volume);

	backgroundMusic.play();
}

void Audio::StopMusic(){
	backgroundMusic.stop();
}

void Audio::PlaySound(std::string file, float volume, bool loop) {
	if (!buffer.loadFromFile("resources/audio/" + file)) {
		std::cout << "ERROR Music file " << file << " not found\n";
	}

	actionSound.setBuffer(buffer);
	actionSound.play();
}

sf::Music Audio::backgroundMusic;
sf::Sound Audio::actionSound;
sf::SoundBuffer Audio::buffer;