#pragma once

#include <windows.h>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <list>
#include <memory>
#include <string>
using FMOD::Sound;
using FMOD::Channel;
using std::cerr;
using std::cout;
using std::endl;
using std::list;
using std::string;

struct SoundData {
	string name;
	string fileDirectory;

	SoundData(const string& name, const string& fileDirectory) {
		this->name = name;
		this->fileDirectory = fileDirectory;
	}
};

struct PlayedSound {
	SoundData soundData;
	Sound* sound;
	Channel* channel;

	PlayedSound(SoundData soundData, Sound* sound = nullptr, Channel* channel = nullptr) : soundData(soundData), sound(sound), channel(channel) { }
};

class AudioManager {
public:
	//Constructors
	AudioManager();

	//Destructors
	~AudioManager();

	void createSound(const string& name, const string& fileDirectory);
	void playSound(const string& soundName, bool loop = false);
	void stopSound(const string& soundName);
	bool isSoundPlaying(const string& soundName);

private:
	FMOD::System* system;
	list<SoundData> soundData;
	list<PlayedSound> playedSounds;

	void init();

	void checkFMODResult(FMOD_RESULT result);
	SoundData getSoundData(const string& soundName);
};