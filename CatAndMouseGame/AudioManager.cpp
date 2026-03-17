#include "AudioManager.h"

AudioManager::AudioManager() {
	//Initialize the AudioManager
	init();
}

/// <summary>
/// Initializes the FMOD libraries.
/// </summary>
void AudioManager::init() {
	checkFMODResult(FMOD::System_Create(&system));
	checkFMODResult(system->init(512, FMOD_INIT_NORMAL, 0));
}

/// <summary>
/// Checks to see if the libraries have loaded properly.
/// </summary>
/// <param name="result">The result of the FMOD query.</param>
void AudioManager::checkFMODResult(FMOD_RESULT result) {
	if (result != FMOD_OK)
		cerr << "FMOD Error: " << FMOD_ErrorString(result) << endl;
}

void AudioManager::createSound(const string& name, const string& fileDirectory) {
	//Store the sound data
	soundData.push_back({ name, fileDirectory });
}

/// <summary>
/// Plays a sound.
/// </summary>
/// <param name="fileDirectory">The directory of the audio file.</param>
void AudioManager::playSound(const string& soundName, bool loop) {
	SoundData currentSound = getSoundData(soundName);

	//If a sound was found, play it
	if (!currentSound.name.empty()) {

		//Create a new sound and channel
		Sound* sound;
		Channel* channel;

		checkFMODResult(system->createSound(currentSound.fileDirectory.c_str(), loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, nullptr, &sound));
		checkFMODResult(system->playSound(sound, nullptr, false, &channel));

		playedSounds.push_back({ currentSound, sound, channel });
		channel->setVolume(0.75f);
	}
}

/// <summary>
/// Stops a sound from playing.
/// </summary>
/// <param name="soundName">The name of the sound.</param>
void AudioManager::stopSound(const string& soundName) {

	for (auto& playedSound : playedSounds) {
		if (playedSound.soundData.name == soundName) {
			if (playedSound.channel)
				checkFMODResult(playedSound.channel->stop());
		}
	}
}

/// <summary>
/// Checks to see if a sound is playing.
/// </summary>
/// <param name="soundName">The name of the sound.</param>
/// <returns>Returns true if the sound is playing. Returns false if the sound is not playing.</returns>
bool AudioManager::isSoundPlaying(const string& soundName) {

	//Look through the list of played sounds
	for (auto& playedSound : playedSounds) {

		//Check the sound name
		if (playedSound.soundData.name == soundName) {
			bool isPlaying = false;

			//If the channel is found, check whether it is playing or not
			if (playedSound.channel)
				playedSound.channel->isPlaying(&isPlaying);

			return isPlaying;
		}
	}
	return false;
}

SoundData AudioManager::getSoundData(const string& soundName) {

	for (auto& sound : soundData) {
		if (sound.name == soundName)
			return sound;
	}

	return { "", "" };
}

AudioManager::~AudioManager() {
	//Clean up FMOD
	for (auto& sound : playedSounds) {
		sound.sound->release();
		sound.channel->stop();
	}

	playedSounds.clear();

	system->close();
	system->release();
}