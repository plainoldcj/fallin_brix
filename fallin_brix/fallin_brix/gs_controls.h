// gs_controls.h

#ifndef __GS_CONTROLS_H__
#define __GS_CONTROLS_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <sfml/graphics.hpp>
#include "gamestate.h"
#include "resource_manager.h"
#include "gs_menu.h"

class GS_Controls : public Gamestate
{
private:
	sf::Sprite _controls;
public:
	GS_Controls(void) { }
	virtual ~GS_Controls(void) { }

	virtual void Init(void);
	virtual void Draw(sf::RenderTarget& renderTarget);
	virtual bool Move(float secsPassed, const sf::Input& input);
	virtual boost::shared_ptr<Gamestate> GetSuccessor(void);
};

#endif