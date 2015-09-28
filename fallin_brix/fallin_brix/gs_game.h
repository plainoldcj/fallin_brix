// gs_game.h

#ifndef __GS_GAME_H__
#define __GS_GAME_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "gamestate.h"
#include "resource_manager.h"
#include "floating_frame.h"
#include "blocks.h"
#include "math.h"
#include "gs_menu.h"
#include "gs_enterscore.h"
#include "explosion.h"
//#include <iostream>

#ifdef _WIN32
#include "xbox_ctrl.h"
#endif

class GS_Game : public Gamestate
{
private:
	struct ActiveBlock
	{
		int index;
		sf::Vector2<int> position;
		int color;
	};
	struct BlockStack
	{
		int rem[4];
		int stack[16];
		bool remFlag;
		int colors[16];

		BlockStack(void)
		{
			for(int i = 0; i < 16; ++i) 
			{
				colors[i] = 0;
				stack[i] = 0;
			}
			remFlag = false;;
		}
	};

	boost::shared_ptr<FmodSound> _drum;
	boost::shared_ptr<FmodSound> _zoom;

	ExplosionManager _expManager;

	FloatingFrame _fieldFrame;
	sf::Sprite _blockSprite;
	ActiveBlock _activeBlock;
	BlockStack _field[20];
	float _timePassed;
	float _fallTimer;
	bool _falling;

	float _blendTimer;

	bool _receivesInput;
	float _delayInput;
	bool _canDrop;
	bool _canRotate;

	E_MenuButtons _next;

	unsigned int _score;

	void AddToField(void);
	bool OutOfField(void);
	bool Collision(void);
	void DropNewBlock(void);
	void DrawShade(sf::RenderTarget& renderTarget);
	void DrawField(sf::RenderTarget& renderTarget);
	void DrawActiveBlock(sf::RenderTarget& renderTarget);

	static sf::Uint8 colorTable[][3];
public:
	GS_Game(void) { }
	~GS_Game(void) { }

	void Init(void);
	void Draw(sf::RenderTarget& renderTarget);
	bool Move(float secsPassed, const sf::Input& input);
	boost::shared_ptr<Gamestate> GetSuccessor(void);
};

#endif