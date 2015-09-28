// floating_frame.cpp

#include "floating_frame.h"

FloatingFrame::FloatingFrame(void)
{
	_center = sf::Vector2<float>(0.0f, 0.0f);
	_needsUpdate = true;
}

void FloatingFrame::SetRadius(float radius)
{
	_radius = radius;
}

void FloatingFrame::SetHalfSize(float width, float height)
{
	_halfSize = sf::Vector2<float>(width, height);
	_needsUpdate = true;
}

void FloatingFrame::SetCenter(const sf::Vector2<float>& center)
{
	_center = center;
	_needsUpdate = true;
}

void FloatingFrame::Move(float secsPassed)
{
	for(int i = 0; i < 4; ++i)
	{
		sf::Vector2<float> direction = _innerVerts[i] - _center;
		Math::NormalizeVector<float>(direction);
		_outerVerts[i].position += _outerVerts[i].sign * direction * _outerVerts[i].strength * secsPassed;
		float d = Math::VectorDistance<float>(_outerVerts[i].position, _innerVerts[i]);
		if(_radius < d) _outerVerts[i].sign *= -1.0f;
		//if(Math::AlmostEqual(d, 0.0f))
		if(Math::VectorDistance(_outerVerts[i].position, _center) <
			Math::VectorDistance(_innerVerts[i], _center))
		{
			_outerVerts[i].sign = 1.0f;
			_outerVerts[i].strength = sf::Randomizer::Random(20.0f, 50.0f);
		};
	}
}

void FloatingFrame::Update(void)
{
	_innerVerts[0] = sf::Vector2<float>(_center.x - _halfSize.x, _center.y + _halfSize.y);
	_innerVerts[1] = sf::Vector2<float>(_center.x + _halfSize.x, _center.y + _halfSize.y);
	_innerVerts[2] = sf::Vector2<float>(_center.x + _halfSize.x, _center.y - _halfSize.y);
	_innerVerts[3] = sf::Vector2<float>(_center.x - _halfSize.x, _center.y - _halfSize.y);

	for(int i = 0; i < 4; ++i) 
	{
		_outerVerts[i].position = _innerVerts[i];
		_outerVerts[i].strength = sf::Randomizer::Random(20.0f, 50.0f);
		_outerVerts[i].sign = 1.0f;
	}

	_needsUpdate = false;
}

void FloatingFrame::Draw(sf::RenderTarget& renderTarget)
{
	if(_needsUpdate) Update();

	sf::Shape innerFrame;
	for(int i = 0; i < 4; ++i) innerFrame.AddPoint(_innerVerts[i]);
	innerFrame.SetColor(sf::Color(50, 50, 50));
	innerFrame.SetBlendMode(sf::Blend::Multiply);
	innerFrame.EnableFill(true);
	renderTarget.Draw(innerFrame);

	for(int i = 0, j = 1; i < 4; ++i, ++j)
	{
		if(3 < j) j = 0;
		sf::Shape poly;
		poly.AddPoint(_innerVerts[i]);
		poly.AddPoint(_outerVerts[i].position);
		poly.AddPoint(_outerVerts[j].position);
		poly.AddPoint(_innerVerts[j]);
		if(i < 2) poly.SetColor(sf::Color(100, 100, 100));
		else poly.SetColor(sf::Color(150, 150, 150));
		poly.SetBlendMode(sf::Blend::Multiply);
		renderTarget.Draw(poly);
	}
}