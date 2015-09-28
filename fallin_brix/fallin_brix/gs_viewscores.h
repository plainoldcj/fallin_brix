// gs_viewscores.h

#ifndef __GS_VIEWSCORES_H__
#define __GS_VIEWSCORES_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>
#include <boost/lexical_cast.hpp>
#include "gamestate.h"
#include "resource_manager.h"
#include "gs_menu.h"
#include "fireworks.h"

#ifdef _WIN32
#include "xbox_ctrl.h"
#endif

class GS_ViewScores : public Gamestate
{
private:
	float _timePassed;
	sf::Sprite _titleSprite;
	sf::String _header;
	sf::String _entry;
	boost::shared_ptr<Fireworks> _fireworks;
public:
	GS_ViewScores(void) { };
	~GS_ViewScores(void) { }
	void Init(void);
	void Draw(sf::RenderTarget& renderTarget);
	bool Move(float secsPassed, const sf::Input& input);
	boost::shared_ptr<Gamestate> GetSuccessor(void);
};

#endif
