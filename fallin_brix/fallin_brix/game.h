// game.h

#ifndef __GAME_H__
#define __GAME_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef _WIN32
#include "xbox_ctrl.h"
#endif

#include "background.h"
#include "fmod_wrapper.h"
#include "gs_menu.h"

class Game
{
private:
	sf::RenderWindow& _renderWindow;
	Background _background;
	boost::shared_ptr<Gamestate> _gamestate;
	bool _isRunning;
	float _viewMoved;
	bool _doTransition;
	boost::shared_ptr<Gamestate> _nextState;

	void AdjustGamestateView(sf::View& view);
public:
	Game(sf::RenderWindow& renderWindow) : _renderWindow(renderWindow) { }
	~Game(void) { }

	bool IsRunning(void) const { return _isRunning; }
	void Init(void);
	void Draw(void);
	void Move(void);
};

#endif