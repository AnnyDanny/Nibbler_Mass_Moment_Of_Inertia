#ifndef _INIBBLER_AUDIO_HPP_
#define _INIBBLER_AUDIO_HPP_

#include <iostream>

class INibblerAudio
{
public:
	virtual				~INibblerAudio() 				= default;
	
	virtual bool		Init()																	= 0;
	virtual void		PlayMusic(const std::string& filename, int loops = -1)					= 0;
	virtual void		StopMusic()																= 0;
	virtual void		ResumeMusic()															= 0;
	virtual void		PlaySFX(const std::string& filename, int loops = 0, int channel = 0)	= 0;

protected:

};

typedef INibblerAudio*		create_audio();
typedef void 				destroy_audio(INibblerAudio*);

#endif
