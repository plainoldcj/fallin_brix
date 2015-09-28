// gamestate.h

#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>
#include <sstream>
#include <fstream>
#include <boost/smart_ptr.hpp>
#include <sfml/graphics.hpp>

class Gamestate
{
protected:
	enum E_MenuButtons
	{
		MB_PLAY = 0,
		MB_CONTROLS,
		MB_HIGHSCORES,
		MB_EXIT,
		MB_SIZE,
		MB_MENU,
		MB_ENTER_SCORE
	};

	sf::View _view;
	static std::vector<std::pair<std::string, unsigned int> > score; 
public:
	typedef std::pair<std::string, unsigned int> scoreEntry_t;
	typedef std::vector<std::pair<std::string, unsigned int> >  score_t;

	virtual ~Gamestate(void) { }

	sf::View& GetView(void) { return _view; }

	static score_t& GetScore(void);
	static void WriteScore(void);

	virtual void Init(void) = 0;
	virtual void Draw(sf::RenderTarget& renderTarget) = 0;
	virtual bool Move(float secsPassed, const sf::Input& input) = 0;
	virtual boost::shared_ptr<Gamestate> GetSuccessor(void) = 0;
};

#endif