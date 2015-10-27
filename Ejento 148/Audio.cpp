#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Audio.h"
#include <string>
#include <iostream>

void Audio::PlayAudio(std::string file, float volume, bool loop){
	if (!music.openFromFile("resources/audio/"+file)) {
		std::cout << "ERROR Music file " << file << " not found\n";
	}
	music.setLoop(loop);
	music.setVolume(volume);

	music.play();
	std::cout << music.getStatus() << "\n";
}

void Audio::StopAudio(){
	music.stop();
}