//#ifdef _SFML
#include "SFMLAudio.h"
#include "../../Utility/MyLogger.h"
#include <SFML/System/Time.hpp>

using Engine::SFMLAudio;

bool Engine::SFMLAudio::Init()
{
	for (auto& sound : m_sfSoundArray)
	{
		sound = new sf::Sound;
	}
	return true;
}

bool Engine::SFMLAudio::PlayMusic(const char * filepath)
{
	// First check if it exists in the music map
	auto musicMapItr = m_pMusicMap.find(filepath);
	if (musicMapItr == m_pMusicMap.end()) //did not find the music in the map
	{
		//create
		m_pMusic = new sf::Music;
		if (!m_pMusic->openFromFile(filepath))
		{
			g_Logger.write(MyLogger::LogLevel::System_Warning, "Fail loading sf::Music.");
			return false;
		}
		//play the music
		m_pMusic->play();
		//add to the music map
		m_pMusicMap.emplace(filepath, std::move(m_pMusic));
	}
	else
	{
		//found it in the map
		musicMapItr->second.get()->play();
	}
	return true;
}

bool Engine::SFMLAudio::PlaySound(const char * filepath)
{
	sf::Sound* sound = GetAvailableSound();
	if (sound)
	{
		// First check if it exists in the sound map
		auto chunkMapItr = m_pChunkMap.find(filepath);
		if (chunkMapItr == m_pChunkMap.end()) //did not find the sound in the map
		{
			//create
			sf::SoundBuffer* pBuffer = new sf::SoundBuffer;
			if (!pBuffer->loadFromFile(filepath))
			{
				g_Logger.write(MyLogger::LogLevel::System_Warning, "Fail loading sf::SoundBuffer.");
				return false;
			}
			//play the chunk
			sound->setBuffer(*pBuffer);
			sound->play();
			//add to the chunk map
			m_pChunkMap.emplace(filepath, std::move(pBuffer));
		}
		else
		{
			//found it in the map
			sound->setBuffer(*(chunkMapItr->second.get()));
			sound->play();
		}
		return true;
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::System_Warning, "Fail to find an available sf::Sound");
		return false;
	}
	
}

void Engine::SFMLAudio::OperateCurrentMusic(EMusicAction action)
{
	switch (action)
	{
	case EMusicAction::kPause:
		m_pMusic->pause();
		break;

	case EMusicAction::kResume:
		m_pMusic->play();
		break;

	case EMusicAction::kStop:
		m_pMusic->stop();
		break;

	default:
		g_Logger.write(MyLogger::LogLevel::Game_Warning, "Unrecognized operation on sfml music");
		break;
	}
}

void Engine::SFMLAudio::OperateCurrentSounds(EMusicAction action)
{
	switch (action)
	{
	case EMusicAction::kPause:
	{
		for (int i = 0; i < g_ArrayNumber; ++i)
		{
			if (m_sfSoundArray[i]->getStatus() != sf::SoundSource::Status::Playing)
			{
				m_sfSoundArray[i]->pause();
			}
		}
	}
		break;

	case EMusicAction::kResume:
	{
		for (int i = 0; i < g_ArrayNumber; ++i)
		{
			if (m_sfSoundArray[i]->getStatus() != sf::SoundSource::Status::Playing)
			{
				m_sfSoundArray[i]->play();
			}
		}
	}
		break;

	case EMusicAction::kStop:
	{
		for (int i = 0; i < g_ArrayNumber; ++i)
		{
			if (m_sfSoundArray[i]->getStatus() != sf::SoundSource::Status::Playing)
			{
				m_sfSoundArray[i]->stop();
			}
		}
	}
		break;

	default:
		g_Logger.write(MyLogger::LogLevel::Game_Warning, "Unrecognized operation on sfml sound");

		break;
	}
}

void Engine::SFMLAudio::FadeInMusic(const char * filepath, int loops, int ms)
{
	/*
	music.setPosition(0, 1, 10); // change its 3D position
	music.setPitch(2);           // increase the pitch
	music.setVolume(50);         // reduce the volume
	music.setLoop(true);         // make it loop
	*/
	g_Logger.write(MyLogger::LogLevel::Game_Warning, "Unfinished operation on sfml sound");
}

void Engine::SFMLAudio::FadeOutMusic(int ms)
{
	/*
	sf::Music::SetVolume() 
	sf::Music::SetAttenuation() //an attenuation value such as 100 will make the sound fade out very quickly as it gets further from the listener. The default value of the attenuation is 1.
	sf::SoundSource::setMinDistance	(float distance) //The "minimum distance" of a sound is the maximum distance at which it is heard at its maximum volume. Further than the minimum distance, 
														it will start to fade out according to its attenuation factor.  A value of 0 ("inside the head of the listener") is an invalid value and
														is forbidden. The default value of the minimum distance is 1.
	*/
}

void Engine::SFMLAudio::FreeMusic(const char * filepath)
{
	auto musicMapItr = m_pMusicMap.find(filepath);
	if (musicMapItr != m_pMusicMap.end())
	{
		auto music = musicMapItr->second.get();
		m_pMusicMap.erase(musicMapItr);
		delete music;
	}
}

void Engine::SFMLAudio::FreeSound(const char * filepath)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr != m_pChunkMap.end())
	{
		auto chunk = chunkMapItr->second.get();
		m_pChunkMap.erase(chunkMapItr);
		delete chunk;
	}
}

sf::Sound* Engine::SFMLAudio::GetAvailableSound()
{
	for (auto& sound : m_sfSoundArray)
	{
		if (sound->getStatus() != sf::SoundSource::Status::Playing)
		{
			return sound;
		}
	}
	return nullptr;
}

void Engine::SFMLAudio::SetMusicVolume(int volume)
{
	m_pMusic->setVolume(float(volume));
}

//find the sound buffer from chunkmap
//check does the buffer in soundArray
//change the sound volumne
void Engine::SFMLAudio::SetSoundVolume(const char * filepath, int volume)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr != m_pChunkMap.end()) 
	{
		auto soundBuffer = chunkMapItr->second.get();
		for (int i = 0; i < g_ArrayNumber; ++i)
		{
			if (m_sfSoundArray[i]->getBuffer() == soundBuffer)
			{
				m_sfSoundArray[i]->setVolume(float(volume));
				break;
			}
		}
	}
	g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail to find the target sound");
}

int Engine::SFMLAudio::GetMusicVolume()
{
	return int(m_pMusic->getVolume());
}

//find the sound buffer from chunkmap
//check does the buffer in soundArray
//get the sound volumne
int Engine::SFMLAudio::GetSoundVolume(const char * filepath)
{
	auto chunkMapItr = m_pChunkMap.find(filepath);
	if (chunkMapItr != m_pChunkMap.end())
	{
		auto soundBuffer = chunkMapItr->second.get();
		for (int i = 0; i < g_ArrayNumber; ++i)
		{
			if (m_sfSoundArray[i]->getBuffer() == soundBuffer)
			{
				return int(m_sfSoundArray[i]->getVolume());
			}
		}
	}
	g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail to find the target sound");
	return -1;
}

//in sfml audio, 100 is full volume, 0 is zero volume
int Engine::SFMLAudio::GetMaxVolume()
{
	return 100;
}

void Engine::SFMLAudio::SetMusicPosition(double position)
{
	m_pMusic->setPlayingOffset(sf::seconds(float(position)));
}
void Engine::SFMLAudio::SetFinishMusicCallback(void(*music_finished)())
{
	/*
	if (music.Stopped == 1) //check music stopped very frame to get the time when the music finishes?
	*/
}
Engine::IAudio::EMusicType Engine::SFMLAudio::GetMusicType(const char * filepath)
{
	return EMusicType::kOthers;
	g_Logger.write(MyLogger::LogLevel::Game_Warning, "SFML does not support this functionality: GetMusicType() ");
}

bool Engine::SFMLAudio::IsMusicPlaying()
{
	if (m_pMusic->getStatus() == sf::SoundSource::Status::Playing)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Engine::SFMLAudio::IsMusicPaused()
{
	if (m_pMusic->getStatus() == sf::SoundSource::Status::Paused)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Engine::SFMLAudio::IsMusicFading()
{
	return false;
	g_Logger.write(MyLogger::LogLevel::Game_Warning, "SFML does not support this functionality: IsMusicFading() ");

}
//#endif