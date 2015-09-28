// background.cpp

#include "background.h"

void Background::Init(void)
{
	_tileImage = ImageManager::GetInstance()->Get("res/background2.png");
}

void Background::RecalculateSize(unsigned int width, unsigned int height)
{
	_repeatX = width / _tileImage->GetWidth() + width % _tileImage->GetWidth() + 2;
	_repeatY = height / _tileImage->GetHeight() + height % _tileImage->GetHeight() + 2;
}

void Background::Draw(sf::RenderTarget& renderTarget)
{
	sf::Sprite sprite(*_tileImage);
	for(unsigned int x = 0; x < _repeatX; ++x)
		for(unsigned int y = 0; y < _repeatY; ++y)
		{
			sprite.SetX((x - 1.0f) * _tileImage->GetWidth() + _offset.x);
			sprite.SetY((y - 1.0f) * _tileImage->GetHeight() + _offset.y);
			renderTarget.Draw(sprite);
		}
}

void Background::Move(const sf::Vector2<float>& scrollVec)
{
	_offset += scrollVec;
	if(_tileImage->GetWidth() * _tileImage->GetWidth() < _offset.x * _offset.x) _offset.x = 0.0f;
	if(_tileImage->GetHeight() * _tileImage->GetHeight() < _offset.y * _offset.y) _offset.y = 0.0f;
}