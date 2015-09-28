// floating_frame.h

#ifndef __FLOATING_FRAME_H__
#define __FLOATING_FRAME_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <sfml/graphics.hpp>
#include "math.h"

class FloatingFrame
{
private:
	struct FloatingVert
	{
		sf::Vector2<float> position;
		float sign;
		float strength;
	};
	FloatingVert _outerVerts[4];
	sf::Vector2<float> _innerVerts[4];
	float _radius;
	sf::Vector2<float> _center;
	sf::Vector2<float> _halfSize;
	bool _needsUpdate;

	void Update(void);
public:
	FloatingFrame(void);
	~FloatingFrame(void) { }

	void SetRadius(float radius);
	void SetHalfSize(float width, float height);
	void SetCenter(const sf::Vector2<float>& center);
	void Move(float secsPassed);
	void Draw(sf::RenderTarget& renderTarget);
};

#endif