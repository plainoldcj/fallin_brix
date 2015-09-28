// background.h

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <sfml/graphics.hpp>
#include "resource_manager.h"

class Background
{
private:
	boost::shared_ptr<sf::Image> _tileImage;
	sf::Vector2<float> _offset;
	unsigned int _repeatX;
	unsigned int _repeatY;
public:
	Background(void) { }
	~Background(void) { }

	void Init(void);
	void RecalculateSize(unsigned int width, unsigned int height);
	void Draw(sf::RenderTarget& renderTarget);
	void Move(const sf::Vector2<float>& scrollVec);
};

#endif