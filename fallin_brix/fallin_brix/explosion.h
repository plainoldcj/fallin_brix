// explosion.h

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <list>
#include "emitter.h"
#include "math.h"

class Explosion : public Emitter {
public:
	typedef Emitter base_t;

	Explosion(const sf::Vector2<float>& pos);
	~Explosion(void) { }

	void ApplyParams(base_t::Particle& p);
};

class ExplosionManager {
private:
	std::list<Explosion> _emitter;
public:
	ExplosionManager(void) { }
	~ExplosionManager(void) { }

	void Explode(const sf::Vector2<float>& pos);

	void Update(float secsPassed);
	void Draw(sf::RenderTarget& renderTarget);
};

#endif