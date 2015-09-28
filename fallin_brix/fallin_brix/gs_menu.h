// gs_menu.h

#ifndef __GS_MENU_H__
#define __GS_MENU_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>
#include "gamestate.h"
#include "resource_manager.h"
#include "gs_game.h"
#include "gs_controls.h"
#include "gs_viewscores.h"

#ifdef _WIN32
#include "xbox_ctrl.h"
#endif

class GS_Menu : public Gamestate
{
private:
	static char* buttonCaptions[];

	float _timePassed;
	float ts;
	sf::Sprite _titleSprite;
	sf::String _button;
	int _selectedButton;
	bool _receivesInput;
	int _oldMouseY;
	float _delayInput;
public:
	GS_Menu(void) { }
	~GS_Menu(void) { }
	void Init(void);
	void Draw(sf::RenderTarget& renderTarget);
	bool Move(float secsPassed, const sf::Input& input);
	boost::shared_ptr<Gamestate> GetSuccessor(void);
};

#endif