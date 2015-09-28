// resource_manager.h

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <map>
#include <boost/shared_ptr.hpp>
#include <sfml/graphics.hpp>
#include "fmod_wrapper.h"

template<class Resource>
class FromFileManager : public sf::NonCopyable
{
private:
	std::map<std::string, boost::shared_ptr<Resource> > _resources;
	FromFileManager(void) { }
public:
	~FromFileManager(void) { }
	
	static boost::shared_ptr<FromFileManager> GetInstance(void)
	{
		static boost::shared_ptr<FromFileManager> instance;
		if(!instance) instance = boost::shared_ptr<FromFileManager>(new FromFileManager);
		return instance;
	}

	boost::shared_ptr<Resource> Get(const std::string& filename)
	{
		std::map<std::string, boost::shared_ptr<Resource> >::iterator resourceIt(_resources.find(filename));
		if(_resources.end() == resourceIt)
		{
			boost::shared_ptr<Resource> resource(new Resource);
			if(!resource->LoadFromFile(filename)) throw std::exception("unable to load resource");
			_resources.insert(std::pair<std::string, boost::shared_ptr<Resource> >(filename, resource));
			return resource;
		}
		return resourceIt->second;
	}
};

template<> class FromFileManager<sf::Font>
{
private:
	std::map<std::string, boost::shared_ptr<sf::Font> > _fonts;
	FromFileManager(void) { }
	sf::Uint32 _charset[191];
public:
	~FromFileManager(void) { }

	void InitCharset(void)
	{
		static sf::Uint32 defaultCharset[] =
		{
			0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
			0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
			0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
			0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
			0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
			0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E,
			0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0x2A, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
			0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
			0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
			0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
			0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
			0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0x00
		};
		for(unsigned int i = 0; i < 191; ++i) _charset[i] = defaultCharset[i];
	}

	static boost::shared_ptr<FromFileManager> GetInstance(void)
	{
		static boost::shared_ptr<FromFileManager> instance;
		if(!instance) 
		{
			instance = boost::shared_ptr<FromFileManager>(new FromFileManager);
			instance->InitCharset();
		}
		return instance;
	}

	boost::shared_ptr<sf::Font> Get(const std::string& filename, unsigned int size)
	{
		std::map<std::string, boost::shared_ptr<sf::Font> >::iterator fontIt(_fonts.find(filename));
		if(_fonts.end() == fontIt)
		{
			boost::shared_ptr<sf::Font> font(new sf::Font);
			if(!font->LoadFromFile(filename, size, _charset)) throw std::exception("unable to load font");
			_fonts.insert(std::pair<std::string, boost::shared_ptr<sf::Font> >(filename, font));
			return font;
		}
		return fontIt->second;
	}
};

template<> class FromFileManager<FmodSound>
{
private:
	std::map<std::string, boost::shared_ptr<FmodSound> > _sounds;
	FmodWrapper _fmodWrapper;
	FromFileManager(void) { }
public:
	~FromFileManager(void) { }
	
	static boost::shared_ptr<FromFileManager> GetInstance(void)
	{
		static boost::shared_ptr<FromFileManager> instance;
		if(!instance) 
		{
			instance = boost::shared_ptr<FromFileManager>(new FromFileManager);
			instance->_fmodWrapper.Init();
		}
		return instance;
	}

	void Update(void) {
		_fmodWrapper.Update();
	}

	boost::shared_ptr<FmodSound> Get(const std::string& filename, bool loop)
	{
		std::map<std::string, boost::shared_ptr<FmodSound> >::iterator soundIt(_sounds.find(filename));
		if(_sounds.end() == soundIt)
		{
			boost::shared_ptr<FmodSound> sound(_fmodWrapper.CreateSound(filename, loop));
			_sounds.insert(std::pair<std::string, boost::shared_ptr<FmodSound> >(filename, sound));
			return sound;
		}
		return soundIt->second;
	}
};

typedef FromFileManager<sf::Image> ImageManager;
typedef FromFileManager<sf::Font> FontManager;
typedef FromFileManager<FmodSound> SoundManager;

#endif