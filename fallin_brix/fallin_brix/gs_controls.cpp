// gs_controls.cpp

#include "gs_controls.h"

void GS_Controls::Init(void)
{
	_controls.SetImage(*ImageManager::GetInstance()->Get("res/controls.png"));
}

void GS_Controls::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.Draw(_controls);
}

bool GS_Controls::Move(float secsPassed, const sf::Input& input)
{
	if(input.IsKeyDown(sf::Key::Escape) || input.IsJoystickButtonDown(0, 3))
		return false;
	return true;
}

boost::shared_ptr<Gamestate> GS_Controls::GetSuccessor(void)
{
	return boost::shared_ptr<Gamestate>(new GS_Menu);
}