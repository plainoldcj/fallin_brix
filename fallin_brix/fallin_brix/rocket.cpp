// rocket.cpp

#include "rocket.h"

Rocket::Rocket(const sf::Vector2<float>& pos) :
base_t(pos, "res/star.png", 0.05f) {
	_sprite.SetImage(*ImageManager::GetInstance()->Get("res/star.png"));
	_sprite.SetCenter((_sprite.GetSize().x / 2.0f),
		(_sprite.GetSize().y / 2.0f));
}

void Rocket::Draw(sf::RenderTarget& renderTarget) {
	base_t::Draw(renderTarget);
	_sprite.SetPosition(GetPos());
	if(!IsDead()) renderTarget.Draw(_sprite);
}

void Rocket::ApplyParams(Rocket::base_t::Particle& p) {
	sf::Randomizer randGen;
	int r = randGen.Random(150, 200);
	int g = randGen.Random(100, 200);
	int b = randGen.Random(100, 200);
	p.col = sf::Color(r, g, b);
	float x = randGen.Random(-1.0f, 1.0f);
	p.dir = sf::Vector2<float>(x, 1.0f);
	p.accel = 40.0f;
	p.decay = 0.5f;
	p.scale = 1.0001f;
	float rot = randGen.Random(-180.0f, 180.0f);
	p.rot = rot;
}