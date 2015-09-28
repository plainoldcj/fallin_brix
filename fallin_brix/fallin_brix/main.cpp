// main.cpp

#define SFML_DYNAMIC

#ifdef _MSC_VER
	#ifdef _DEBUG
		#pragma comment(lib, "sfml-system-d.lib")
		#pragma comment(lib, "sfml-window-d.lib")
		#pragma comment(lib, "sfml-graphics-d.lib")
	#else
		#pragma comment(lib, "sfml-system.lib")
		#pragma comment(lib, "sfml-window.lib")
		#pragma comment(lib, "sfml-graphics.lib")
	#endif
	#ifdef _WIN64
		#pragma comment(lib, "fmodex64_vc.lib")
	#else
		#pragma comment(lib, "fmodex_vc.lib")
	#endif
#endif

#ifdef _WIN32
#include "win32_enumeration.h"
typedef Win32ModeEnumeration ModeEnumeration;
#else
#include "enumeration.h"
#endif

#include <iostream>
#include "game.h"

int main(int argc, char* argv[])
{
	ModeEnumeration enum_;
	if(!enum_.DoEnumeration()) return 1;

	unsigned long styleFlag = sf::Style::Close;
	if((1 < argc) && (std::string(argv[1]) == std::string("resizable"))) styleFlag |= sf::Style::Resize;
	if(enum_.IsFullscreen()) styleFlag = sf::Style::Fullscreen;

	sf::RenderWindow window(enum_.GetSelectedMode(), "Fallin' Brix, Christian Jaeger", styleFlag);

	Game theGame(window);
	try { theGame.Init(); }
	catch(std::exception& err)
	{
		std::cerr << "exception: " << err.what() << std::endl;
		return -1;
	}
	
	while(window.IsOpened() && theGame.IsRunning())
	{
		sf::Event event_;
		if(window.GetEvent(event_))
		{
			switch(event_.Type)
			{
			case sf::Event::KeyPressed:
				if(sf::Key::F4 == event_.Key.Code)
					window.Close();
				break;
			case sf::Event::Closed:
				window.Close();
				break;
			}
		}
		theGame.Move();
		window.Clear();
		theGame.Draw();
		window.Display();
	}
	return 0;
}