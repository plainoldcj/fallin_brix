// emitter.h

#ifndef __EMITTER_H__
#define __EMITTER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <list>
#include <sfml/graphics.hpp>
#include "resource_manager.h"
#include "math.h"

class Emitter {
protected:
	struct Particle {
		sf::Vector2<float> pos;
		sf::Vector2<float> dir;
		sf::Color col;
		float scale;
		float accel;
		float health;
		float decay;
		float rot;

		Particle() {
			pos = sf::Vector2<float>(0.0f, 0.0f);
			dir = sf::Vector2<float>(0.0f, 0.0f);
			col = sf::Color(0, 0, 0);
			scale = 1.0f;
			accel = 1.0f;
			health = 100.0f;
			decay = 1.0f;
			rot = 0.0f;
		}
	};
private:
	std::list<Particle> _alive;
	std::list<Particle> _dead;
	sf::Sprite _sprite;
	sf::Vector2<float> _pos;

	bool _active;

	float _timePassed;
	float _spawnTick;
	int _spawnCount;
protected:
	void SetSpawnCount(int spawnCount) { _spawnCount = spawnCount; }
public:
	Emitter(const sf::Vector2<float>& pos,
		const std::string& image,
		float spawnTick);
	virtual ~Emitter(void) { }

	sf::Vector2<float>& GetPos(void) { return _pos; }
	void SetPos(const sf::Vector2<float>& pos) { _pos = pos; }
	void Update(float secsPassed);
	void Spawn(void);

	void SetActive(bool active) { _active = active; }
	bool IsDead(void) { return _alive.empty() && !_active; }

	virtual void Draw(sf::RenderTarget& renderTarget);

	virtual void ApplyParams(Particle& p) = 0;
};

#endif 