#pragma once
#include "Components.h"
#include <map>
#include "AssetManager.h"
#include <algorithm>

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
	std::map<std::string, Mix_Chunk*> sounds;

	AudioComponent() = default;
	~AudioComponent() {}

	void addSound(std::string asset_id, std::string local_id = "") {
		std::string id = local_id;
		if (id.compare("") == 0) {
			id = asset_id;
		}
		sounds.emplace(id, Game::assets->GetSound(asset_id));
	}

	void PlaySound(std::string soundName,
					int baseVolume = MIX_MAX_VOLUME, float distance = 0) {
		//Get Sound
		Mix_Chunk* sound = sounds[soundName];
		//Calc & set volume
		unsigned int volume = CalcVolume(baseVolume, distance);
		std::cout << "volume: " << volume << std::endl;
		Mix_VolumeChunk(sound, volume);
		//Play sound
		Mix_PlayChannel(-1, sound, 0);
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

	}
};