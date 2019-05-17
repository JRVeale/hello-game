#pragma once

#include "Components.h"
#include "Vector2D.h"
#include "Timer.h"

class SwordComponent : public Component {
private:
	Timer timer = Timer();

public:
	//show that timers work
	SwordComponent() {
		timer.Start(2000, true);
	}
	void update() override {
		int check = timer.Check();
		if (check == 1) {
			std::cout << "Timer!" << std::endl;
		}
	}
};