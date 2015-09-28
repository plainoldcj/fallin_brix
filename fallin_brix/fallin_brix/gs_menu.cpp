// gs_menu.cpp

#include "gs_menu.h"

char* GS_Menu::buttonCaptions[]  = {
	"play now!",
	"view Controls",
	"some motivation",
	"good bye"
};

void GS_Menu::Init(void)
{
	_titleSprite.SetImage(*ImageManager::GetInstance()->Get("res/title3.png"));
	_titleSprite.SetCenter(_titleSprite.GetSize().x / 2,
				_titleSprite.GetSize().y / 2);
	_titleSprite.SetPosition(sf::Vector2<float>(400.0f, 100.0f));

	_button.SetFont(*FontManager::GetInstance()->Get("res/menu_font.ttf", 100));
	_button.SetSize(50);

	_selectedButton = 0;
	_timePassed = 0.0f;
	_receivesInput = true;
}

void GS_Menu::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.Draw(_titleSprite);

	float tri = abs(sinf(_timePassed * 5.0f));
	for(int i = 0; i < MB_SIZE; ++i)
	{
		_button.SetText(buttonCaptions[i]);
		_button.SetCenter(_button.GetRect().GetWidth() / 2,
			_button.GetRect().GetHeight() / 2);
		_button.SetPosition(400.0f, 300.0f + i * 50.0f);
		if(_selectedButton == i)
		{
			_button.SetColor(sf::Color(0, 0, 0, 200));
			_button.SetScale(tri / 5.0f + 1.0f, tri / 10.0f + 1.0f);
		}
		renderTarget.Draw(_button);
		_button.SetScale(1.0f, 1.0f);
		_button.SetColor(sf::Color(255, 255, 255, 200));
	}
}

bool GS_Menu::Move(float secsPassed, const sf::Input& input)
{
	if(input.IsKeyDown(sf::Key::Return) || 
		input.IsMouseButtonDown(sf::Mouse::Left) ||
		input.IsJoystickButtonDown(0, 0)) // note: 'a' on xbox ctrl
		return false;

	// NOTE: no mouse, game is only controlled with keyboard
	/*int mouseY = input.GetMouseY(); // TODO: window -> view coord trans	
	if(_oldMouseY != mouseY)
	{
		for(int i = 0; i < MB_SIZE; ++i)
		{
			if(mouseY > 300 + i * 50 &&
				mouseY < 350 + i * 50)
			{
				_selectedButton = i;
			}
		}
	}*/

#ifdef _WIN32
	XBoxCtrl::GetInstance()->Update(secsPassed);
#endif

	if(_receivesInput)
	{
		if(input.IsKeyDown(sf::Key::Up) || -50.0f > input.GetJoystickAxis(0, sf::Joy::AxisY)) 
		{
#ifdef _WIN32
			XBoxCtrl::GetInstance()->Rumble(10000, 1000, 0.2f);
#endif
			//_oldMouseY = mouseY;
			_receivesInput = false;
			_selectedButton--;
		}
		if(input.IsKeyDown(sf::Key::Down) || 50.0f < input.GetJoystickAxis(0, sf::Joy::AxisY)) 
		{
#ifdef _WIN32
			XBoxCtrl::GetInstance()->Rumble(10000, 1000, 0.2f);
#endif
			//_oldMouseY = mouseY;
			_receivesInput = false;
			_selectedButton++;
		}
		if(MB_SIZE <= _selectedButton) _selectedButton = MB_SIZE - 1;
		if(0 > _selectedButton) _selectedButton = 0;
		_delayInput = 0.0f;
	}
	else
	{
		_delayInput += secsPassed;
		if(0.2f < _delayInput)
			_receivesInput = true;
	}

	float tri = abs(sinf(_timePassed));
	_titleSprite.SetScale(tri / 5.0f + 0.7f, tri / 10.0f + 0.7f);
	unsigned char alpha = static_cast<unsigned char>(150.0f * tri) + 105;
	_titleSprite.SetColor(sf::Color(255, 255, 255, alpha));

	_timePassed += secsPassed;
	return true;
}

boost::shared_ptr<Gamestate> GS_Menu::GetSuccessor(void)
{
	switch(_selectedButton)
	{
	case MB_PLAY:
		return boost::shared_ptr<Gamestate>(new GS_Game);
	case MB_CONTROLS:
		return boost::shared_ptr<Gamestate>(new GS_Controls);
	case MB_HIGHSCORES:
		return boost::shared_ptr<Gamestate>(new GS_ViewScores);
	default:
		return boost::shared_ptr<Gamestate>();
	};
}