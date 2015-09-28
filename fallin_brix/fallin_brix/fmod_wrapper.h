// fmod_wrapper.h

#ifndef __FMOD_WRAPPER_H__
#define __FMOD_WRAPPER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <fmod.hpp>

class FmodWrapper;

class FmodSound
{
	friend class FmodWrapper;
private:
	FMOD::System* _system;
	FMOD::Sound* _sound;

	FmodSound(FMOD::System* system) : _system(system) { }
public:
	~FmodSound(void) { }

	void Play(void);
};

class FmodWrapper
{
private:
	FMOD::System* _system;
public:
	FmodWrapper(void) { }
	~FmodWrapper(void) { Drop(); }

	void Init(void);
	void Drop(void);
	void Update(void) { _system->update(); }
	boost::shared_ptr<FmodSound> CreateSound(const std::string& filename, bool loop);
};

#endif