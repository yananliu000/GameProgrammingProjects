#ifdef _SDL
#include "SDLAudio.h"
#include "../../Utility/MyLogger.h"

using Engine::SDLAudio;

bool Engine::SDLAudio::Init()
{
	int soundFileTypes = MIX_INIT_MP3 | MIX_INIT_OGG;

	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	if (Mix_Init(soundFileTypes) != soundFileTypes)
	{
		return false;
	}
	return true;
}

bool Engine::SDLAudio::PlayMusic(const char * filepath)
{
	Mix_PlayMusic(GetMusic(filepath), -1);
	return true;
}


bool Engine::SDLAudio::PlaySound(const char * filepath)
{
	Mix_PlayChannel(-1, GetSound(filepath), 0); //play the chunk
	return true;
}

void Engine::SDLAudio::OperateCurrentMusic(EMusicAction action)
{
	switch (action)
	{
	case EMusicAction::kPause:
		Mix_PauseMusic();
		break;

	case EMusicAction::kResume:
		Mix_ResumeMusic();
		break;

	case EMusicAction::kStop:
		Mix_HaltMusic();
		break;

	default:
		g_Logger.write(MyLogger::LogLevel::Game_Warning, "Unrecognized operation on sdl music");
		break;
	}
}

void Engine::SDLAudio::OperateCurrentSounds(EMusicAction action)
{
	switch (action)
	{
	case EMusicAction::kPause:
		Mix_Pause(-1); //-1 for all active channels
		break;

	case EMusicAction::kResume:
		Mix_Resume(-1);
		break;

	case EMusicAction::kStop:
		Mix_HaltChannel(-1);
		break;

	case EMusicAction::kRewind:
		Mix_RewindMusic();
		break;
	default:
		g_Logger.write(MyLogger::LogLevel::Game_Warning, "Unrecognized operation on sdl sound");
		break;
	}
}

void Engine::SDLAudio::FadeInMusic(const char * filepath, int loops, int ms)
{
	if (Mix_FadeInMusic(GetMusic(filepath), loops, ms) == -1)
	{
		g_Logger.write(MyLogger::LogLevel::Game_Warning, "sdl FadeInMusic fails");
	}
}

void Engine::SDLAudio::FadeOutMusic(int ms)
{
	Mix_FadeOutMusic(ms);
}

void Engine::SDLAudio::FreeMusic(const char * filepath)
{
	auto musicMapItr = m_pMusicMap.find(filepath);
	if (musicMapItr != m_pMusicMap.end())
	{
		auto music = musicMapItr->second.get();
		m_pMusicMap.erase(musicMapItr);
		Mix_FreeMusic(music);
	}
}

void Engine::SDLAudio::FreeSound(const char * filepath)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr != m_pChunkMap.end())
	{
		auto chunk = chunkMapItr->second.get();
		m_pChunkMap.erase(chunkMapItr);
		Mix_FreeChunk(chunk);
	}
}

Mix_Music * Engine::SDLAudio::GetMusic(const char * filepath)
{
	auto musicMapItr = m_pMusicMap.find(filepath);
	if (musicMapItr == m_pMusicMap.end())
	{
		std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> pMusic(Mix_LoadMUS(filepath), &Mix_FreeMusic);
		m_pMusicMap.emplace(filepath, std::move(pMusic));
		return pMusic.get();
	}
	else
	{
		return musicMapItr->second.get();
	}
}

Mix_Chunk * Engine::SDLAudio::GetSound(const char * filepath)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr == m_pChunkMap.end()) 
	{
		std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> pChunk(Mix_LoadWAV(filepath), &Mix_FreeChunk);
		m_pChunkMap.emplace(filepath, std::move(pChunk));
		return pChunk.get();
	}
	else
	{
		return chunkMapItr->second.get();
	}
}

void Engine::SDLAudio::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void Engine::SDLAudio::SetSoundVolume(const char* filepath,int volume)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr == m_pChunkMap.end())
	{
		Mix_VolumeChunk(chunkMapItr->second.get(), volume);
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail to find the target sound");
	}
}

int Engine::SDLAudio::GetMusicVolume()
{
	//Set the volume to volume, if it is 0 or greater, and return the previous volume setting. 
	return Mix_VolumeMusic(-1);
}

int Engine::SDLAudio::GetSoundVolume(const char * filepath)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr == m_pChunkMap.end())
	{
		return Mix_VolumeChunk(chunkMapItr->second.get(), -1);
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail to find the target sound");
		return -1;
	}
}

int Engine::SDLAudio::GetMaxVolume()
{
	return MIX_MAX_VOLUME;
}

void Engine::SDLAudio::SetMusicPosition(double position)
{
	if (Mix_SetMusicPosition(60.0) != -1) 
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Setting music to position fails");
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::Game_Info, "Setting music to position");
	}
}

void Engine::SDLAudio::SetFinishMusicCallback(void(*music_finished)())
{
	Mix_HookMusicFinished(music_finished);
}

Engine::IAudio::EMusicType Engine::SDLAudio::GetMusicType(const char * filepath)
{
	auto musicMapItr = m_pMusicMap.find(filepath);
	if (musicMapItr != m_pMusicMap.end())
	{
		switch (Mix_GetMusicType(musicMapItr->second.get()))
		{
		case MUS_CMD:
			return kCommand;
			break;
		case MUS_WAV:
			return kWav;
			break;
		case MUS_MOD:
			return kMod;
			break;
		case MUS_MID:
			return kMidi;
			break;
		case MUS_OGG:
			return kOgg;
			break;
		case MUS_MP3:
			return kMp3;
			break;
		default:
			g_Logger.write(MyLogger::LogLevel::Game_Warning, "Unknown music is playing");
			break;
		}
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::Game_Warning, "The request music havn't been loaded yet");

	}
	return kOthers;

}

bool Engine::SDLAudio::IsMusicPlaying()
{
	if (Mix_PlayingMusic() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Engine::SDLAudio::IsMusicPaused()
{
	if (Mix_PausedMusic() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Engine::SDLAudio::IsMusicFading()
{
	if (Mix_FadingMusic() == MIX_NO_FADING)
	{
		return false;
	}
	else
	{
		return true;
	}
}
#endif