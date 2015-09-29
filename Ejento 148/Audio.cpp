#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Audio.h"
#include <string>
#include <iostream>

void Audio::musicStart(std::string file, float volume){
	sf::Music backgroundMusic;
	if (!backgroundMusic.openFromFile(file)) {
		std::cout << "ERROR Music file " << file << " not found" << std::endl;
	}
	backgroundMusic.setLoop(1);
	backgroundMusic.setVolume(volume);

	backgroundMusic.play();
	std::cout << backgroundMusic.getStatus() << std::endl;
}

void Audio::musicStop(char * file){

}

void Audio::soundPlay(char * file){

}
