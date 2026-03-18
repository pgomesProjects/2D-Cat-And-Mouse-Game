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

class SoundData {
public:
	//Constructors
	SoundData(const string& name, const string& fileDirectory);
	SoundData(const string& name, const string& directory, const bool& loop);

	//GETTERS
	string GetName();
	string GetFileDirectory();
	bool IsLooping();
	Sound* GetSound();

	//SETTERS
	void SetSound(Sound* sound);

private:
	string name;
	string fileDirectory;
	bool loop;
	Sound* sound;
};

struct ActiveSound {
	string name;
	Channel* channel;
};

class AudioManager {
public:
	//Constructors
	AudioManager();

	//Destructors
	~AudioManager();

	void CreateSound(const string& name, const string& fileDirectory, bool loop = false);
	void PlaySound(const string& soundName);
	void StopSound(const string& soundName);
	bool IsSoundPlaying(const string& soundName);
	void Update();

private:
	FMOD::System* system;
	list<SoundData*> soundMap;
	list<ActiveSound> activeSounds;

	void init();

	void CheckFMODResult(FMOD_RESULT result);
	SoundData* GetSoundData(const string& soundName);
};