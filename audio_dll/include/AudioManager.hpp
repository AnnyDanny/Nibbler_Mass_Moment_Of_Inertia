#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

#include "../../includes/iNibblerAudio.hpp"
#include "SDL_mixer.h"
#include <iostream>
#include <string>
#include <map>

//**************************************************************************************************
//	AudioManager
//--------------------------------------------------------------------------------------------------
class AudioManager : public INibblerAudio
{

public:
	AudioManager()			= default;
	virtual ~AudioManager()	= default;
 
 	virtual bool		Init()																	override;
	virtual void		PlayMusic(const std::string& filename, int loops = -1)					override;
	virtual void		StopMusic()																override;
	virtual void		ResumeMusic()															override;
	virtual void		PlaySFX(const std::string& filename, int loops = 0, int channel = 0)	override;

private:
	Mix_Music*			GetMusic(const std::string& filename);
	Mix_Chunk*			GetSeffect(const std::string& filename);

	std::map<std::string, Mix_Music *>	mMusic;
	std::map<std::string, Mix_Chunk *>	mSeffects;
};

extern "C" INibblerAudio* createAudioEntity();

extern "C" void deletAudioEntity(INibblerAudio*);

#endif