// game.cpp

#include "game.h"

void Game::AdjustGamestateView(sf::View& view)
{
	view.SetCenter(400.0f, 300.0f);
	view.SetHalfSize(400.0f, 300.0f);
	view.Zoom(800.0f / _renderWindow.GetWidth());
}

void Game::Init(void)
{
	_background.Init();
	_background.RecalculateSize(_renderWindow.GetWidth(), _renderWindow.GetHeight());

	_gamestate = boost::shared_ptr<Gamestate>(new GS_Menu());
	_gamestate->Init();
	AdjustGamestateView(_gamestate->GetView());

	boost::shared_ptr<FmodSound> bgmusic = SoundManager::GetInstance()->Get("res/bgmusic.mid", true);
	bgmusic->Play();

	_doTransition = false;
	_isRunning = true;

	Gamestate::GetScore();
}

void Game::Draw(void)
{
	_background.Draw(_renderWindow);

	_renderWindow.SetView(_gamestate->GetView());
	_gamestate->Draw(_renderWindow);
	_renderWindow.SetView(_renderWindow.GetDefaultView());

	if(_doTransition)
	{
		_renderWindow.SetView(_nextState->GetView());
		_nextState->Draw(_renderWindow);
		_renderWindow.SetView(_renderWindow.GetDefaultView());
	}
}

void Game::Move(void)
{
	float secsPassed = _renderWindow.GetFrameTime();

	if(_doTransition)
	{
		_background.Move(sf::Vector2<float>(0.0f, 800.0f * secsPassed));
		_viewMoved += 800.0f * secsPassed;
		_gamestate->GetView().Move(0.0f, -800.0f * secsPassed);
		_nextState->GetView().Move(0.0f, -800.0f * secsPassed);
		float viewHeight = _gamestate->GetView().GetRect().GetHeight();
		float distance = viewHeight + (_renderWindow.GetHeight() - viewHeight);
		if(distance < _viewMoved)
		{
			_gamestate = _nextState;
			_doTransition = false;
		}
	}
	else
	{
		_background.Move(sf::Vector2<float>(0.0f, 20.0f * secsPassed));
		if(!_gamestate->Move(secsPassed, _renderWindow.GetInput()))
		{
			_nextState = _gamestate->GetSuccessor();
			if(!_nextState)
			{
				_isRunning = false;
				return;
			}
#ifdef _WIN32
			XBoxCtrl::GetInstance()->Rumble(0, 0, 0.0f);
#endif
			_nextState->Init();
			sf::View& view = _nextState->GetView();
			AdjustGamestateView(view);
			view.Move(0.0f, static_cast<float>(_renderWindow.GetHeight()));
			_doTransition = true;
			_viewMoved = 0.0f;
		}
	}
}