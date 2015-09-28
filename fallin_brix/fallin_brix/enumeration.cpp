// enumeration.cpp

#include "enumeration.h"

bool ModeEnumeration::DoEnumeration(void)
{
	std::vector<sf::VideoMode> validModes;
	unsigned int modeCount = sf::VideoMode::GetModesCount() - 1;
	std::cout << "available videomodes:" << std::endl;
	for(unsigned int i = 0; i < modeCount; ++i)
	{
		sf::VideoMode mode = sf::VideoMode::GetMode(i);
		if(800 > mode.Width || 600 > mode.Height) continue; 
		std::cout << "[" << i << "] " << mode.Width << "x" << mode.Height 
			<< ", " << mode.BitsPerPixel << "bit" << std::endl;
		validModes.push_back(mode);
	}
	unsigned int selectedMode;
	std::cout << "select mode: ";
	std::cin >> selectedMode;
	char fullscreen;
	std::cout << "go fullscreen? [y/n]: ";
	std::cin >> fullscreen;
	if(0 > selectedMode || modeCount < selectedMode)
	{
		std::cerr << "invalid mode, using default" << std::endl;
		selectedMode = 0;
	}
	_mode = validModes[selectedMode];
	switch(fullscreen)
	{
	case 'Y':
	case 'y':
		_fullscreen = true;
		break;
	case 'N':
	case 'n':
		_fullscreen = false;
		break;
	default:
		std::cerr << "invalid input, starting in windowed mode" << std::endl;
		_fullscreen = false;
	};
	return true;
}