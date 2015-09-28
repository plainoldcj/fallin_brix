// gs_viewscores.cpp

#include "gs_viewscores.h"

void GS_ViewScores::Init(void) {
	_header.SetFont(*FontManager::GetInstance()->Get("res/menu_font.ttf", 100));
	_header.SetSize(100);
	_header.SetText("Highscores!");
	_header.SetColor(sf::Color(10, 10, 10));
	_header.SetCenter(_header.GetRect().GetWidth() / 2,
		_header.GetRect().GetHeight() / 2);
	_header.SetPosition(400.0f, 50.0f);

	_entry.SetFont(*FontManager::GetInstance()->Get("res/menu_font.ttf", 100));
	_entry.SetSize(50);

	_fireworks = boost::shared_ptr<Fireworks>(new Fireworks(2.0f));
}

void GS_ViewScores::Draw(sf::RenderTarget& renderTarget)
{
	_fireworks->Draw(renderTarget);
	renderTarget.Draw(_header);

	int i = 0;
	for(score_t::iterator scoreIt(score.begin());
		scoreIt != score.end(); ++scoreIt) {
			if(i == 0) {
				_entry.SetColor(sf::Color(255, 0, 0));
			} else {
				_entry.SetColor(sf::Color(0, 0, 0, 255 - 20 * i));
			}
			_entry.SetText(scoreIt->first + " " + boost::lexical_cast<std::string>(scoreIt->second));
			_entry.SetCenter(_entry.GetRect().GetWidth() / 2,
				_entry.GetRect().GetHeight() / 2);
			_entry.SetPosition(400.0f, 200.0f + 32.0f * i);
			renderTarget.Draw(_entry);
			++i;
	}
}

bool GS_ViewScores::Move(float secsPassed, const sf::Input& input)
{
	if(input.IsKeyDown(sf::Key::Escape) || input.IsJoystickButtonDown(0, 3))
		return false;

	_fireworks->Update(secsPassed);
	return true;
}

boost::shared_ptr<Gamestate> GS_ViewScores::GetSuccessor(void)
{
	return boost::shared_ptr<Gamestate>(new GS_Menu);
}