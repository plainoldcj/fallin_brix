// fireworks.cpp

#include "fireworks.h"

void Fireworks::Draw(sf::RenderTarget& renderTarget) {
	for(std::list<RocketMover>::iterator rocketIt(_rockets.begin());
		rocketIt != _rockets.end(); ++rocketIt) {
			rocketIt->Draw(renderTarget);
	}
}

void Fireworks::Update(float secsPassed) {
	_timePassed += secsPassed;
	if(_timePassed > _spawnTick) {
		_timePassed = 0.0f;
		sf::Randomizer randGen;
		float x = randGen.Random(50.0f, 750.0f);
		float accel = randGen.Random(200.0f, 300.0f);
		RocketMover rocket(sf::Vector2<float>(x, 600.0f),
			sf::Vector2<float>(0.0f, -1.0f), accel);
		_rockets.push_back(rocket);
		_rocketSound->Play();
	}
	for(std::list<RocketMover>::iterator rocketIt(_rockets.begin());
		rocketIt != _rockets.end(); ++rocketIt) {
			rocketIt->Move(secsPassed);
			Emitter& emitter = rocketIt->GetEmitter();
			if(emitter.GetPos().y < 0.0f) {
				emitter.SetActive(false);
			}
			if(emitter.IsDead()) {
				rocketIt = _rockets.erase(rocketIt);
			}
	}
}