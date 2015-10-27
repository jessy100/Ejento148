#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Audio.h"
#include <string>
#include <iostream>

void Audio::MusicStart(std::string file, float volume){
	if (!music.openFromFile("resources/audio/"+file)) {
		std::cout << "ERROR Music file " << file << " not found\n";
	}
	music.setLoop(true);
	music.setVolume(volume);

	music.play();
	std::cout << music.getStatus() << "\n";
}

void Audio::MusicStop(char * file){

}

void Audio::PlaySound(char * file){

}
