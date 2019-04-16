#pragma once
#include "Components.h"
#include <bitset>
#include <array>

enum statusLabels : std::size_t {
	none,
	hot,
	cold,
	burning,
	frozen,
	wet,
	poisoned,
	suffocating,
	healing,
	resting,
	invincible
};

constexpr std::size_t maxStatuses = 32;

using StatusBitSet = std::bitset<maxStatuses>;
using StatusArray = std::array<float, maxStatuses>;

class StatusComponent : public Component {
public:
	StatusBitSet statuses;
	StatusArray multipliers;	//100 for normal

	float maxHealth = 1;
	float health = 1;

	StatusComponent(float hp) {
		maxHealth = health = hp;
		for (int i = 0; i < maxStatuses; i++) {
			statuses[i] = false;	//No statuses at start
			multipliers[i] = 1;	//All multipliers set normal
		}
	}

	StatusComponent(unsigned int hp, StatusArray mults) {
		maxHealth = health = hp;
		for (int i = 0; i < maxStatuses; i++) {
			statuses[i] = false;	//No statuses at start
		}
		multipliers = mults;
	}

	void init() override {

	}

	void update() override {
		if (health <= 0) {
			//std::cout << " died!" << std::endl;
			health = 0;
		}
	}

	void damage(int hp, statusLabels type = none) {
		health -= hp * multipliers[type];
	}

	void setStatus(statusLabels status) {
		statuses[status] = true;
	}

	void removeStatus(statusLabels status) {
		statuses[status] = false;
	}
};