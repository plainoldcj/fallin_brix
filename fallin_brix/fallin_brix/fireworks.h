// fireworks.h

#ifndef __FIREWORKS_H__
#define __FIREWORKS_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <list>
#include "rocket.h"

class Fireworks {
private:
	boost::shared_ptr<FmodSound> _rocketSound;
	std::list<RocketMover> _rockets;
	float _timePassed;
	float _spawnTick;
public:
	Fireworks(float spawnTick) : _timePassed(spawnTick), _spawnTick(spawnTick) {
		_rocketSound = SoundManager::GetInstance()->Get("res/zoom.wav", false);
	}
	~Fireworks(void) { }

	void Draw(sf::RenderTarget& renderTarget);
	void Update(float secsPassed);
};

#endif