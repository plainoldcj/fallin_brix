// gs_game.cpp

#include "gs_game.h"

sf::Uint8 GS_Game::colorTable[][3] = {
	{ 199, 243, 239 },
	{ 210, 243, 199 },
	{ 228, 189, 205 },
	{ 245, 246, 163 },
	{ 251, 211, 159 },
	{ 206, 199, 243 },
	{ 243, 199, 218 }
};

void GS_Game::DrawShade(sf::RenderTarget& renderTarget)
{
	int y = _activeBlock.position.y;
	while(!Collision()) _activeBlock.position.y++;
	_activeBlock.position.y--;
	_blockSprite.SetColor(sf::Color(10, 10, 10, 100));
	for(int i = 0; i < MAPSIZE; ++i)
	{
		for(int j = 0; j < MAPSIZE; ++j)
		{
			if(0 > _activeBlock.position.y + i) continue;
			if(0 < s_blocks[_activeBlock.index].map[MAPSIZE * i + j])
			{
				sf::Vector2<float> position;
				position.x = 200.0f + (_activeBlock.position.x + j) * BLOCKSIZE;
				position.y = 50.0f + (_activeBlock.position.y + i) * BLOCKSIZE;
				_blockSprite.SetPosition(position);
				renderTarget.Draw(_blockSprite);
			}
		}
	}
	_activeBlock.position.y = y;
}

void GS_Game::DropNewBlock(void)
{
	_activeBlock.color = sf::Randomizer::Random(0, 6);
	_activeBlock.index = sf::Randomizer::Random(0, 23);
	_activeBlock.position.x = 10 + s_blocks[_activeBlock.index].x;
	_activeBlock.position.y = s_blocks[_activeBlock.index].y;
}

void GS_Game::DrawActiveBlock(sf::RenderTarget& renderTarget)
{
	int entry = _activeBlock.color;
	sf::Color color(colorTable[entry][0], colorTable[entry][1], 
			colorTable[entry][2]);
	_blockSprite.SetColor(color);
	for(int i = 0; i < MAPSIZE; ++i)
	{
		for(int j = 0; j < MAPSIZE; ++j)
		{
			if(0 > _activeBlock.position.y + i) continue;
			if(0 < s_blocks[_activeBlock.index].map[MAPSIZE * i + j])
			{
				sf::Vector2<float> position;
				position.x = 200.0f + (_activeBlock.position.x + j) * BLOCKSIZE;
				position.y = 50.0f + (_activeBlock.position.y + i) * BLOCKSIZE;
				_blockSprite.SetPosition(position);
				renderTarget.Draw(_blockSprite);
			}
		}
	}
}

void GS_Game::AddToField(void)
{
	_drum->Play();

	sf::Randomizer randGen;
	sf::Vector2<float> position;
	int x = _activeBlock.position.x + randGen.Random(0, 2);
	int y = _activeBlock.position.y + randGen.Random(0, 2);
	position.x = 200.0f + x * BLOCKSIZE;
	position.y = 50.0f + y * BLOCKSIZE;
	_expManager.Explode(position);

	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			_field[_activeBlock.position.y + i].stack[_activeBlock.position.x + j] +=
				std::min<int>(s_blocks[_activeBlock.index].map[MAPSIZE * i + j], 1);
			if(0 < s_blocks[_activeBlock.index].map[MAPSIZE * i + j])
			{
				_field[_activeBlock.position.y + i].colors[_activeBlock.position.x + j] =
					_activeBlock.color;
			}
		}
	}

	int total = 0;
	for(int i = 0; i < 20; ++i)
	{
		int occ = 0;
		for(int j = 0; j < 16; ++j)
			occ += _field[i].stack[j];
		if(15 < occ)
		{
			_field[i].remFlag = true;
			total++;
		}
	}
	_score += (100 * total);
	if(0 < total)
	{
#ifdef _WIN32
		XBoxCtrl::GetInstance()->Rumble(20000, 2000, 2.0f);
#endif

		_falling = false;
		_blendTimer = 0.0f;
	}
}

bool GS_Game::OutOfField(void)
{
	if(_activeBlock.position.x < 0 || _activeBlock.position.x > 11)
	{
		for(int i = 0; i < 4; ++i)
		{
			for(int j = 0; j < 4; ++j)
			{
				if(0 < s_blocks[_activeBlock.index].map[MAPSIZE * i + j])
				{
					if(_activeBlock.position.x + j < 0  ||
						_activeBlock.position.x + j > 15)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool GS_Game::Collision(void)
{
	if(20 < _activeBlock.position.y - s_blocks[_activeBlock.index].y) return true;

	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			if(_activeBlock.position.x + j < 16 && _activeBlock.position.y + i > 0)
			{
				int fieldOcc = _field[_activeBlock.position.y + i].stack[_activeBlock.position.x + j];
				if((0 < fieldOcc) && (0 < s_blocks[_activeBlock.index].map[MAPSIZE * i + j]))
				{
					return true;
				}
			}
		}
	}

	return false;
}

void GS_Game::Init(void)
{
	_blockSprite.SetImage(*ImageManager::GetInstance()->Get("res/brick.png"));
	_blockSprite.Resize(BLOCKSIZE, BLOCKSIZE);
	DropNewBlock();

	_drum = SoundManager::GetInstance()->Get("res/drum.wav", false);
	_zoom = SoundManager::GetInstance()->Get("res/blink.wav", false);

	_fieldFrame.SetCenter(sf::Vector2<float>(400.0f, 300.0f));
	_fieldFrame.SetHalfSize(200, 250);
	_fieldFrame.SetRadius(50.0f);

	_fallTimer = 0.0f;
	_timePassed = 0.0f;

	_delayInput = 0.0f;
	_receivesInput = true;

	for(int i = 0; i < 16; ++i)
	{
		for(int j = 0; j < 20; ++j)
		{
			_field[i].stack[j] = 0;
		}
	}

	_falling = true;
	_canDrop = true;
	_canRotate = true;

	_score = 0;
}

void GS_Game::Draw(sf::RenderTarget& renderTarget)
{
	_fieldFrame.Draw(renderTarget);

	DrawShade(renderTarget);
	DrawField(renderTarget);
	DrawActiveBlock(renderTarget);

	_expManager.Draw(renderTarget);
}

void GS_Game::DrawField(sf::RenderTarget& renderTarget)
{
	for(int i = 0; i < 20; ++i)
	{
		for(int j = 0; j < 16; ++j)
		{
			if(_field[i].stack[j] > 0) 
			{
				float x = 200.0f + j * BLOCKSIZE;
				float y = 50.0f + i * BLOCKSIZE;
				_blockSprite.SetPosition(x, y);
				int entry = _field[i].colors[j];
				sf::Uint8 alpha = 255;
				if(_field[i].remFlag == true)
				{
					alpha = static_cast<int>(255.0f * sin(_blendTimer));
				}
				sf::Color color(colorTable[entry][0], colorTable[entry][1], 
					colorTable[entry][2], alpha);
				_blockSprite.SetColor(color);
				renderTarget.Draw(_blockSprite);
			}
		}
	}
}

bool GS_Game::Move(float secsPassed, const sf::Input& input)
{
#ifdef _WIN32
	XBoxCtrl::GetInstance()->Update(secsPassed);
#endif

	_expManager.Update(secsPassed);

	SoundManager::GetInstance()->Update();

	_timePassed += secsPassed;
	_fallTimer += secsPassed;

	if(Collision()) 
	{
		if(_activeBlock.position.y <= 0)
		{
			_next = MB_ENTER_SCORE;
			return false;
		}

		_activeBlock.position.y--;
		AddToField();
		DropNewBlock();
	}

	if(input.IsKeyDown(sf::Key::Escape) || input.IsJoystickButtonDown(0, 3))
	{
		_next = MB_MENU;
		// _next = MB_ENTER_SCORE;
		return false;
	}

	if(_canDrop && _falling)
	{
		if(input.IsKeyDown(sf::Key::Down) || input.IsJoystickButtonDown(0, 0))
		{
#ifdef _WIN32
			XBoxCtrl::GetInstance()->Rumble(10000, 20000, 0.3f);
#endif
			while(!Collision()) _activeBlock.position.y++;
			_activeBlock.position.y--;
			
			if(_activeBlock.position.y <= 0)
			{
				_next = MB_ENTER_SCORE;
				return false;
			}

			AddToField();
			DropNewBlock();

			_fallTimer = 0.0f;
			_canDrop = false;
		}
	}
	if(!_canDrop)
	{
		if(!input.IsKeyDown(sf::Key::Down) && !input.IsJoystickButtonDown(0, 0))
			_canDrop = true;
	}

	if(_canRotate)
	{
		if(input.IsKeyDown(sf::Key::Up) || input.IsJoystickButtonDown(0, 1))
		{
			int current = _activeBlock.index;
			int next = _activeBlock.index + s_blocks[current].next;
			int px1, py1, px2, py2;
			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
				{
					if(BLOCK_PIVOT == s_blocks[current].map[MAPSIZE * i + j])
					{
						px1 = i; py1 = j;
					}
					if(BLOCK_PIVOT == s_blocks[next].map[MAPSIZE * i + j])
					{
						px2 = i; py2 = j;
					}
				}
			}
			_activeBlock.index = next;
			sf::Vector2<int> pos = _activeBlock.position;
			int x = _activeBlock.position.x += (px2 - px1);
			int y = _activeBlock.position.y += (py2 - py1);

			if(OutOfField() || Collision())
			{
				int i;
				for(i = 1; i < 4; ++i)
				{
					_activeBlock.position.x = x - i;
					if(!OutOfField()) break;
					_activeBlock.position.x = x + i;
					if(!OutOfField()) break;
				}

				if(3 <= i || Collision()) 
				{
					_activeBlock.position = pos;
					_activeBlock.index = current;
				}
			}
#ifdef _WIN32
			XBoxCtrl::GetInstance()->Rumble(10000, 1000, 0.5f);
#endif
			_zoom->Play();
			_canRotate = false;
		}
	}

	if(!_canRotate)
	{
		if(!input.IsKeyDown(sf::Key::Up) && !input.IsJoystickButtonDown(0, 1))
			_canRotate = true;
	}

	if(_receivesInput)
	{
		if(_falling)
		{
			if(50.0f < input.GetJoystickAxis(0, sf::Joy::AxisY))
			{
				_activeBlock.position.y++;
				if(Collision()) _activeBlock.position.y--;

				_fallTimer = 0.0f;
				_delayInput = 0.0f;
				_receivesInput = false;
			}
			if(-50.0f > input.GetJoystickAxis(0, sf::Joy::AxisY))
			{
				for(int i = 0; i < 2; ++i)
				{
					_activeBlock.position.y++;
					if(Collision()) _activeBlock.position.y--;
				}

				_fallTimer = 0.0f;
				_delayInput = 0.0f;
				_receivesInput = false;
			}
		}
		if(input.IsKeyDown(sf::Key::Left) || -50.0f > input.GetJoystickAxis(0, sf::Joy::AxisX)) 
		{
			_activeBlock.position.x--;
			if(OutOfField() || Collision()) _activeBlock.position.x++;

			_receivesInput = false;
			_delayInput = 0.0f;
		}
		if(input.IsKeyDown(sf::Key::Right) || 50.0f < input.GetJoystickAxis(0, sf::Joy::AxisX)) 
		{
			_activeBlock.position.x++;
			if(OutOfField() || Collision()) _activeBlock.position.x--;

			_receivesInput = false;
			_delayInput = 0.0f;
		}
	}
	else
	{
		_delayInput += secsPassed;
		if(0.1f < _delayInput)
			_receivesInput = true;
	}

	if(_falling)
	{
		if(_fallTimer > 0.5f)
		{
			_activeBlock.position.y++;
			_fallTimer = 0.0f;
		}
	}
	else
	{
		_blendTimer += secsPassed;
		if(2.0f < _blendTimer)
		{
			for(int i = 19; i >= 1; --i)
			{
				if(_field[i].remFlag)
				{
					for(int j = 0; j < i; ++j)
					{
						for(int k = 0; k < 16; ++k)
						{
							_field[i - j].stack[k] = _field[i - j - 1].stack[k];
							_field[i - j].remFlag = _field[i - j - 1].remFlag;
						}
					}
					++i;
				}
			}
			_falling = true;
		}
	}

	_fieldFrame.Move(secsPassed);
	return true;
}

boost::shared_ptr<Gamestate> GS_Game::GetSuccessor(void)
{
	switch(_next)
	{
	case MB_MENU:
		return boost::shared_ptr<Gamestate>(new GS_Menu);
	case MB_ENTER_SCORE:
		return boost::shared_ptr<Gamestate>(new GS_EnterScore(_score));
	default:
		return boost::shared_ptr<Gamestate>();
	}
}