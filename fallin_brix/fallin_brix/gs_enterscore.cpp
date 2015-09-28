// gs_enterscore.cpp

#include "gs_enterscore.h"

GS_EnterScore::GS_EnterScore(unsigned int pscore) : _score(pscore)
{
}

GS_EnterScore::~GS_EnterScore(void)
{
}

void GS_EnterScore::Init(void)
{
	_bigFont = *FontManager::GetInstance()->Get("res/menu_font.ttf", 100);
	_smallFont = *FontManager::GetInstance()->Get("res/menu_font.ttf", 50);

	_head.SetText("Great Job!\n      Enter your Name:");
	_head.SetFont(_smallFont);
	_head.SetSize(50);
	_head.SetCenter(_head.GetRect().GetWidth() / 2,
			_head.GetRect().GetHeight() / 2);
	_head.SetPosition(400.0f, 100.0f);
	_head.SetColor(sf::Color(0, 0, 0, 200));

	_timePassed = 0.0f;
	_delayInput = 0.0f;

	_fireworks = boost::shared_ptr<Fireworks>(new Fireworks(2.0f));
}

bool comparePairs(const Gamestate::scoreEntry_t& lhp,
				 const Gamestate::scoreEntry_t& rhp)
{
	return lhp.second > rhp.second;
}

bool GS_EnterScore::Move(float secsPassed, const sf::Input& input)
{
	_timePassed += secsPassed;

	if(_receivesInput && _name.length() < 24)
	{
		if(input.IsKeyDown(sf::Key::Return))
		{
			score.push_back(scoreEntry_t(std::string(_name.c_str()), _score));
			std::sort(score.begin(), score.end(), comparePairs);
			while(10 < score.size()) score.pop_back();
			WriteScore();
			return false;
		}

		if(input.IsKeyDown(sf::Key::Code(8)) || input.IsKeyDown(sf::Key::Back))
		{
			_name = _name.substr(0, _name.length() - 1);
			_receivesInput = false;
			_delayInput = 0.0f;
		}

		bool shift = input.IsKeyDown(sf::Key::LShift) ||
			input.IsKeyDown(sf::Key::RShift);
		for(int i = 97; i < 123; ++i)
		{
			if(input.IsKeyDown(sf::Key::Code(i)))
			{
				int c = i - (shift ? 32 : 0);
				_name.append(1, static_cast<char>(c));
				_receivesInput = false;
				_delayInput = 0.0f;
				break;
			}
		}
	}
	else
	{
		_delayInput += secsPassed;
		if(0.15f < _delayInput)
			_receivesInput = true;
	}

	_fireworks->Update(secsPassed);

	return true;
}

void GS_EnterScore::Draw(sf::RenderTarget &renderTarget)
{
	float tri = abs(sinf(_timePassed * 5.0f));
	_head.SetScale(tri / 5.0f + 1.0f, tri / 10.0f + 1.0f);

	sf::String name(_name.c_str(), _smallFont);
	name.SetSize(50);
	name.SetColor(sf::Color(0, 0, 0));
	name.SetCenter(name.GetRect().GetWidth() / 2,
		name.GetRect().GetHeight() / 2);
	name.SetPosition(400.0f, 300.0f);

	_fireworks->Draw(renderTarget);
	
	renderTarget.Draw(_head);
	renderTarget.Draw(name);
}

boost::shared_ptr<Gamestate> GS_EnterScore::GetSuccessor(void) { return boost::shared_ptr<Gamestate>(new GS_Menu); }