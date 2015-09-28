// enumeration.h

#ifndef __ENUMERATION_H__
#define __ENUMERATION_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <iostream>
#include <vector>
#include <sfml/graphics.hpp>

class ModeEnumeration
{
private:
	sf::VideoMode _mode;
	bool _fullscreen;
public:
	ModeEnumeration(void) { }
	~ModeEnumeration(void) { }

	bool DoEnumeration(void);
	sf::VideoMode GetSelectedMode(void) { return _mode; }
	bool IsFullscreen(void) { return _fullscreen; }
};

#endif