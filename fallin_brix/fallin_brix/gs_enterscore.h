// gs_enterscore.h

#ifndef __GS_ENTERSCORE_H__
#define __GS_ENTERSCORE_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <fstream>
#include <iostream>
#include <algorithm>
#include "gamestate.h"
#include "resource_manager.h"
#include "fireworks.h"
#include "gs_menu.h"

class GS_EnterScore : public Gamestate
{
private:
	float _timePassed;
	float _delayInput;
	bool _receivesInput;

	unsigned int _score;
	std::string _name;

	sf::String _head;
	sf::Font _bigFont;
	sf::Font _smallFont;

	boost::shared_ptr<Fireworks> _fireworks;
public:
	GS_EnterScore(unsigned int score);
	virtual ~GS_EnterScore(void);

	void Init(void);
	void Draw(sf::RenderTarget& renderTarget);
	bool Move(float secsPassed, const sf::Input& input);
	boost::shared_ptr<Gamestate> GetSuccessor(void);;
};

#endif