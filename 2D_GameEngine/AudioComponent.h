#pragma once
#include "Components.h"
#include <map>
#include "AssetManager.h"
#include <algorithm>

struct SoundEffect {
	Mix_Chunk* sound = NULL;
	int current_channel = -1;
};

class AudioComponent : public Component {
private:
	TransformComponent* transform;

	unsigned int CalcVolume(int baseVolume = MIX_MAX_VOLUME, float distance = 0) {
		unsigned int volume = baseVolume; //&min is zero
		if (distance != 0 && volume != 0) {
			unsigned int dist_abs = abs(static_cast<int>(distance/80));
			//Log
			//volume = static_cast<int>(baseVolume / pow(dist_abs + 1, 2));
			//Lin
			volume = static_cast<int>(baseVolume / (dist_abs + 1));
		}
		return volume;
	}

public:
	//std::map<const char*, Mix_Music> musics;
	std::map<std::string, SoundEffect> soundEffects;

	AudioComponent() {
		addSoundEffect("missing_sound");
	}
	~AudioComponent() {}

	void addSoundEffect(std::string asset_id, std::string local_id = "") {
		std::string id = local_id;
		if (id.compare("") == 0) {
			id = asset_id;
		}
		Mix_Chunk* p_sound = Game::assets->GetSound(asset_id);
		SoundEffect s_effect = { p_sound, -1 };
		soundEffects.emplace(id, s_effect);

	}

	void PlaySound(std::string soundName,
					int baseVolume = MIX_MAX_VOLUME, float distance = 0) {
		
		std::string id = soundName;
		
		//Check if exists...
		if (soundEffects.count(id) != 1) {
			//There is no sound effect with this id in this AudioComponent
			std::cout << "[Entitity name here] does not have a sound effect with the ID " << id << std::endl;
			id = "missing_sound";
		}
		
		//Check if already playing...
		int current_ch = soundEffects[id].current_channel;
		if (current_ch != -1) {
			//Should already be playing
			//Check still is playing
			if (Mix_Playing(current_ch) != 0) {
				//Still playing
				//Return -(channel currently playing on)
				return;
			}
			else {
				//Finished playing
				//Set current_channel back to -1 to show free
				soundEffects[id].current_channel = -1;
			}
		}
		//Not already playing, go ahead!
		//Get Sound
		Mix_Chunk* sound = soundEffects[id].sound;
		//Calc volume
		unsigned int volume = CalcVolume(baseVolume, distance);
		std::cout << "volume: " << volume;
		if (volume > 0) {
			//Set volume
			Mix_VolumeChunk(sound, volume);
			//Play sound (& set the current_channel flag for the soundEffect
			soundEffects[id].current_channel = Mix_PlayChannel(-1, sound, 0);
			std::cout << " played on channel " << soundEffects[id].current_channel;
		}
		std::cout << std::endl;
	}

	/*void addMusic(std::string id) {

	}

	void PlayMusic(const char* musicName,
					int baseVolume = MIX_MAX_VOLUME, float distance = 0) {
		//Get Music
		Mix_Music* music = Game::assets->GetMusic(musicName);
		//Calc & Set Volume
		unsigned int volume = CalcVolume(baseVolume, distance);
		Mix_VolumeMusic();
	}*/

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			//if don't already have transform, make one
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		//Update soundEffects' current_channels if they've finished playing..
		/*This should deal with channels not being 'freed' in SoundEffect,
			and leading to them blocking eachother in PlaySound*/
		//Unless threading allows sound to finish while update() is occuring...
		for (auto& sf : soundEffects) {
			int current_ch = sf.second.current_channel;
			if (current_ch != -1) {
				if (Mix_Playing(current_ch) == 0) {
					//Has finished playing
					//(and hasn't yet been recognised by a repeated call to PlaySound)
					sf.second.current_channel = -1;
				}
			}
		}
	}
};