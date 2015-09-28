// rocket.h

#ifndef __ROCKET_H__
#define __ROCKET_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "emitter.h"

class Rocket : public Emitter {
private:
	sf::Sprite _sprite;
public:
	typedef Emitter base_t;

	Rocket(const sf::Vector2<float>& pos);
	~Rocket(void) { }

	void ApplyParams(base_t::Particle& p);
	void Draw(sf::RenderTarget& renderTarget);
};

class RocketMover {
private:
	Rocket _emitter;
	sf::Vector2<float> _dir;
	float _accel;
public:
	RocketMover(const sf::Vector2<float>& pos,
		const sf::Vector2<float>& dir,
		float accel) : _emitter(pos), _dir(dir), _accel(accel) { }
	~RocketMover(void) { }

	Emitter& GetEmitter(void) { return _emitter; }

	void Move(float secsPassed) {
		_emitter.Update(secsPassed);
		_emitter.SetPos(_emitter.GetPos() + (_dir * _accel * secsPassed));
	}

	void Draw(sf::RenderTarget& renderTarget) {
		_emitter.Draw(renderTarget);
	}
};

#endif