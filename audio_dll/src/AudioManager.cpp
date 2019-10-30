#include "../include/AudioManager.hpp"

#define EXPORT __attribute__((visibility("default")))

//==================================================================================================
//	AudioManager::Init
//--------------------------------------------------------------------------------------------------
EXPORT bool AudioManager::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Error initializing SDL2_mixer " << Mix_GetError() <<std::endl;
		return false;
	}
	return true;
}
//==================================================================================================
//	AudioManager::PlayMusic
//--------------------------------------------------------------------------------------------------
EXPORT void AudioManager::PlayMusic(const std::string& filename, int loops)
{
	Mix_PlayMusic(GetMusic(filename), loops);
}
//==================================================================================================
//	AudioManager::StopMusic
//--------------------------------------------------------------------------------------------------
EXPORT void AudioManager::StopMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}
//==================================================================================================
//	AudioManager::ResumeMusic
//--------------------------------------------------------------------------------------------------
void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}
//==================================================================================================
//	AudioManager::PlaySFX
//--------------------------------------------------------------------------------------------------
EXPORT void AudioManager::PlaySFX(const std::string& filename, int loops, int channel)
{
	Mix_PlayChannel(channel, GetSeffect(filename), loops);
}

Mix_Music* AudioManager::GetMusic(const std::string& filename)
{
	std::string fullpath;
	fullpath.append("resourses/sound/" + filename);

	if (mMusic[fullpath] == nullptr)
	{
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mMusic[fullpath] == nullptr)
		{
			std::cout << "Error opening " << fullpath << "music " << Mix_GetError() <<std::endl; 
		}
	}
	return mMusic[fullpath];
}

Mix_Chunk* AudioManager::GetSeffect(const std::string& filename)
{
	std::string fullpath;
	fullpath.append("resourses/sound/" + filename);

	if (mSeffects[fullpath] == nullptr)
	{
		mSeffects[fullpath] = Mix_LoadWAV(fullpath.c_str());
		if (mSeffects[fullpath] == nullptr)
		{
			std::cout << "Error opening " << fullpath << "sound effect " << Mix_GetError() <<std::endl;
		}
	}
	return mSeffects[fullpath];
}

EXPORT INibblerAudio* createAudioEntity()
{
	return new AudioManager();
}

EXPORT void deletAudioEntity(INibblerAudio* entity)
{
	delete entity;
}
