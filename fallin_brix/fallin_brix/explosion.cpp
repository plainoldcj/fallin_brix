// explosion.cpp

#include "explosion.h"

Explosion::Explosion(const sf::Vector2<float>& pos) :
base_t(pos, "res/circle.png", 0.5f) { }

void Explosion::ApplyParams(Emitter::Particle &p) {
	sf::Randomizer randGen;
	int r = randGen.Random(150, 200);
	int g = randGen.Random(100, 200);
	int b = randGen.Random(100, 200);
	p.col = sf::Color(r, g, b);
	float x = randGen.Random(-1.0f, 1.0f);
	float y = randGen.Random(-1.0f, 1.0f);
	p.dir = sf::Vector2<float>(x, y);
	Math::NormalizeVector<float>(p.dir);
	p.accel = 100.0f;
	p.decay = 0.5f;
	p.scale = 1.0001f;
	float rot = randGen.Random(-180.0f, 180.0f);
	p.rot = rot;
}

void ExplosionManager::Explode(const sf::Vector2<float> &pos) {
	Explosion exp_(pos);
	for(int i = 0; i < 10; ++i) { exp_.Spawn(); }
	exp_.SetActive(false);
	_emitter.push_back(exp_);
}

void ExplosionManager::Update(float secsPassed) {
	for(std::list<Explosion>::iterator expIt(_emitter.begin());
		expIt != _emitter.end();) {
			expIt->Update(secsPassed);
			if(expIt->IsDead()) {
				expIt = _emitter.erase(expIt);
			} else {
				++expIt;
			}
	}
}

void ExplosionManager::Draw(sf::RenderTarget& renderTarget) {
	for(std::list<Explosion>::iterator expIt(_emitter.begin());
		expIt != _emitter.end(); ++expIt) {
			expIt->Draw(renderTarget);
	}
}