// emitter.cpp

#include "emitter.h"

Emitter::Emitter(const sf::Vector2<float>& pos,
				 const std::string& image,
				 float spawnTick) : _pos(pos), _spawnTick(spawnTick), _timePassed(0.0f), _spawnCount(1), _active(true) {
	_sprite.SetImage(*ImageManager::GetInstance()->Get(image.c_str()));
	_sprite.SetCenter((_sprite.GetSize().x / 2.0f),
		(_sprite.GetSize().y / 2.0f));
}

void Emitter::Update(float secsPassed) {
	_timePassed += secsPassed;
	if(_active) {
		if(_timePassed > _spawnTick) {
			_timePassed = 0.0f;
			for(int i = 0; i < _spawnCount; ++i) {
				Spawn();
			}
		}
	}
	for(std::list<Particle>::iterator aliveIt(_alive.begin());
		aliveIt != _alive.end();) {
			float fade = aliveIt->decay * secsPassed;
			aliveIt->col.a -= fade;
			aliveIt->health -= fade;
			aliveIt->scale -= fade;
			aliveIt->pos += (aliveIt->dir * aliveIt->accel * secsPassed);
			if(aliveIt->health <= 0.0f || aliveIt->scale <= 0.2f) {
				aliveIt = _alive.erase(aliveIt);
			} else {
				++aliveIt;
			}
	}
}

void Emitter::Spawn(void) {
	Particle p;
	p.pos = _pos;
	ApplyParams(p);
	_alive.push_back(p);
	_alive.push_back(p);
}

void Emitter::Draw(sf::RenderTarget& renderTarget) {
	for(std::list<Particle>::iterator aliveIt(_alive.begin());
		aliveIt != _alive.end(); ++aliveIt) {
			_sprite.SetPosition(aliveIt->pos);
			// _sprite.SetRotation(aliveIt->rot);
			_sprite.SetScale(sf::Vector2<float>(aliveIt->scale, aliveIt->scale));
			_sprite.SetColor(aliveIt->col);
			renderTarget.Draw(_sprite);
	}
}