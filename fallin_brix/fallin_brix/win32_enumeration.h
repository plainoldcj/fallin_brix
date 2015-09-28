// win32_enumeration.h

#ifndef __WIN32_MODE_ENUMERATION_H__
#define __WIN32_MODE_ENUMERATION_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <windowsx.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <sfml/graphics.hpp>
#include "resource.h"

#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

class Win32ModeEnumeration
{
private:
	sf::VideoMode _mode;
	bool _fullscreen;
public:
	Win32ModeEnumeration(void) { }
	~Win32ModeEnumeration(void) { }

	bool DoEnumeration(void);
	sf::VideoMode GetSelectedMode(void) { return _mode; }
	bool IsFullscreen(void) { return _fullscreen; }
};

#endif