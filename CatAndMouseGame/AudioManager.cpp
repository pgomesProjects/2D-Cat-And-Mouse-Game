#include "AudioManager.h"

SoundData::SoundData(const string& name, const string& fileDirectory){
	this->name = name;
	this->fileDirectory = fileDirectory;
	this->loop = false;
}

SoundData::SoundData(const string& name, const string& fileDirectory, const bool& loop) {
	this->name = name;
	this->fileDirectory = fileDirectory;
	this->loop = loop;
}

string SoundData::GetName() {
	return this->name;
}

string SoundData::GetFileDirectory() {
	return this->fileDirectory;
}

bool SoundData::IsLooping() {
	return this->loop;
}

Sound* SoundData::GetSound() {
	return this->sound;
}

void SoundData::SetSound(Sound* sound) {
	this->sound = sound;
}

AudioManager::AudioManager() {
	//Initialize the AudioManager
	init();
}

/// <summary>
/// Initializes the FMOD libraries.
/// </summary>
void AudioManager::init() {
	CheckFMODResult(FMOD::System_Create(&system));
	CheckFMODResult(system->init(512, FMOD_INIT_NORMAL, 0));
}

/// <summary>
/// Checks to see if the libraries have loaded properly.
/// </summary>
/// <param name="result">The result of the FMOD query.</param>
void AudioManager::CheckFMODResult(FMOD_RESULT result) {
	if (result != FMOD_OK)
		cerr << "FMOD Error: " << FMOD_ErrorString(result) << endl;
}

/// <summary>
/// Creates a sound
/// </summary>
/// <param name="name"></param>
/// <param name="fileDirectory"></param>
/// <param name="loop"></param>
void AudioManager::CreateSound(const string& name, const string& fileDirectory, bool loop) {
	SoundData* data = new SoundData(name, fileDirectory, loop);

	//Create the sound pointer
	Sound* sound;
	CheckFMODResult(system->createSound(data->GetFileDirectory().c_str(), data->IsLooping() ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, nullptr, &sound));
	data->SetSound(sound);

	//Add it to the sound list
	soundMap.push_back(data);
}

/// <summary>
/// Plays a sound.
/// </summary>
/// <param name="fileDirectory">The directory of the audio file.</param>
void AudioManager::PlaySound(const string& soundName) {
	SoundData* currentSound = GetSoundData(soundName);
	
	//If no sound was found, return
	if (!currentSound)
		return;

	//Play the sound and output to a channel
	Channel* channel;
	CheckFMODResult(system->playSound(currentSound->GetSound(), nullptr, false, &channel));
	channel->setVolume(0.75f);

	//Add it to the active sounds list
	activeSounds.push_back({ soundName, channel });
}

/// <summary>
/// Stops a sound from playing.
/// </summary>
/// <param name="soundName">The name of the sound.</param>
void AudioManager::StopSound(const string& soundName) {

	for (auto& sound : activeSounds) {
		if (sound.name == soundName && sound.channel) {
			sound.channel->stop();
		}
	}
}

/// <summary>
/// Checks to see if a sound is playing.
/// </summary>
/// <param name="soundName">The name of the sound.</param>
/// <returns>Returns true if the sound is playing. Returns false if the sound is not playing.</returns>
bool AudioManager::IsSoundPlaying(const string& soundName) {

	//Look through the list of played sounds
	for (auto& playedSound : activeSounds) {

		//Check the sound name
		if (playedSound.name == soundName) {

			bool isPlaying = false;
			//If the channel is found, check whether it is playing or not
			if (playedSound.channel && playedSound.channel->isPlaying(&isPlaying) == FMOD_OK && isPlaying)
				return true;
			else
				return false;
		}
	}
	return false;
}

/// <summary>
/// Updates the list of active sounds to remove any sounds that are not playing.
/// </summary>
void AudioManager::Update() {
	system->update();

	//Look through all active sounds
	for (auto it = activeSounds.begin(); it != activeSounds.end(); ) {

		bool isPlaying = false;
		//If the channel is found, check whether it is playing or not. If so, continue
		if (it->channel && it->channel->isPlaying(&isPlaying) == FMOD_OK && isPlaying)
			++it;
		//If it's not playing, remove it
		else
			it = activeSounds.erase(it);
	}
}

SoundData* AudioManager::GetSoundData(const string& soundName) {

	for (auto& sound : soundMap) {
		if (sound->GetName() == soundName)
			return sound;
	}

	return nullptr;
}

AudioManager::~AudioManager() {
	//Release all sounds and delete them
	for (auto& sound : soundMap) {
		sound->GetSound()->release();
		delete sound;
	}

	soundMap.clear();
	activeSounds.clear();

	//Close FMOD
	system->close();
	system->release();
}