#pragma once
#include <fmod.hpp>
#include <windows.h>


// for some reason, attempting to use functions outside of the class
// that use FMOD::System functions results in linker errors
class Audio
{
private:
	Audio();
	FMOD::System* system;
	FMOD::Sound* effect1;
	FMOD::Sound* stream1;
	bool isPlaying;

public:

	FMOD::Channel* channel;

	inline static Audio* Ins()
	{
		static Audio ins;
		return &ins;
	}
	void Init()
	{
		FMOD_CAPS			caps;
		FMOD_RESULT			result;
		FMOD_SPEAKERMODE	speakermode;
		int					numdrivers;
		unsigned int		version;
		char				name[256];

		FMOD::System_Create(&system);	// create the system

		// set up the system properly, based on hardware

		system->getVersion(&version);

		if(version < FMOD_VERSION)	return;

		system->getNumDrivers(&numdrivers);

		if(numdrivers == 0)			
			system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		else
		{
			system->getDriverCaps(0, &caps, 0, 0, &speakermode);
			system->setSpeakerMode(speakermode);
			system->getDriverInfo(0, name, 256, 0);
			result = system->init(100, FMOD_INIT_NORMAL, 0);
			if(caps & FMOD_CAPS_HARDWARE_EMULATED)	
				system->setDSPBufferSize(1024, 10);

			if(strstr(name, "SigmaTel"))
			{
				system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT,
												0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			}
			 
			if(result = FMOD_ERR_OUTPUT_CREATEBUFFER)
			{
				system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
				system->init(100, FMOD_INIT_NORMAL, 0);
			}
		}

		system->createSound("pop.wav",	FMOD_DEFAULT, 0, &effect1);		// load the tada effect
	}
	void PlayEffect()
	{
		//channel->isPlaying(&isPlaying);		// get the state of the audio
		//if(soundKeyDown && !isPlaying)		// if the space bar is being pressed and the sound is not already playing
		//{
			system->playSound(FMOD_CHANNEL_FREE, effect1, false, &channel);	// play sound
		//}


		
	}
};

