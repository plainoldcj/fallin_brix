// fmod_wrapper.cpp

#include "fmod_wrapper.h"

void FmodSound::Play(void)
{
	_system->playSound(FMOD_CHANNEL_FREE, _sound, false, NULL);
}

void FmodWrapper::Init(void)
{
	/*
	RECOMMENDED STARTUP SEQUENCE
	*/

    FMOD_RESULT      result;
    unsigned int     version;
    int              numdrivers;
    FMOD_SPEAKERMODE speakermode;
    FMOD_CAPS        caps;
    char             name[256];

    result = FMOD::System_Create(&_system);
    if(FMOD_OK != result) throw std::exception("fmod: System_Create faield");
    
    result = _system->getVersion(&version);
    if(FMOD_OK != result) throw std::exception("fmod: getVersion failed");

    if (version < FMOD_VERSION)
		throw std::exception("using depreciated version of fmod, update or use sfml audio");
    
    result = _system->getNumDrivers(&numdrivers);
    if(FMOD_OK != result) throw std::exception("fmod: getNumDrivers failed");

    if (numdrivers == 0)
    {
        result = _system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        if(FMOD_OK != result) throw std::exception("fmod: setOutput failed");
    }
    else
    {
        result = _system->getDriverCaps(0, &caps, 0, 0, &speakermode);
        if(FMOD_OK != result) throw std::exception("fmod: getDriverCaps failed");

        result = _system->setSpeakerMode(speakermode);
        if(FMOD_OK != result) throw std::exception("fmod: setSpeakerMode failed");

        if (caps & FMOD_CAPS_HARDWARE_EMULATED)
        {
            result = _system->setDSPBufferSize(1024, 10);
			if(FMOD_OK != result) throw std::exception("fmod: setDSPBufferSize failed");
        }

        result = _system->getDriverInfo(0, name, 256, 0);
		if(FMOD_OK != result) throw std::exception("fmod: getDriverInfo failed");

        if (strstr(name, "SigmaTel"))
        {
            result = _system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
			if(FMOD_OK != result) throw std::exception("fmod: setSoftwareFormat failed");
        }
    }

    result = _system->init(100, FMOD_INIT_NORMAL, 0);
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
    {
        result = _system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if(FMOD_OK != result) throw std::exception("fmod: setSpeakerMode failed");
            
        result = _system->init(100, FMOD_INIT_NORMAL, 0);
		if(FMOD_OK != result) throw std::exception("fmod: init failed");
    }
}

void FmodWrapper::Drop(void)
{
	_system->release();
}

boost::shared_ptr<FmodSound> FmodWrapper::CreateSound(const std::string& filename, bool loop)
{
	boost::shared_ptr<FmodSound> sound(new FmodSound(_system));
	unsigned int flag = FMOD_DEFAULT;
	if(!loop)
	{
		flag |= FMOD_LOOP_OFF;
	}
	else
	{
		flag |= FMOD_LOOP_NORMAL;
	}
	if(FMOD_OK != _system->createSound(filename.c_str(), flag, NULL, &sound->_sound))
		throw std::exception("unable to load sound");
	return sound;
}