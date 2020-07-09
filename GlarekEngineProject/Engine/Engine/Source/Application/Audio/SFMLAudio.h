#pragma once
//SFML supports the audio file formats WAV, OGG/Vorbis and FLAC. Due to licensing issues MP3 is not supported.
//sound: interface of soundbuffer 
//soudnbuffer: raw data
//music: stream

/** \file SFMLAudio.h */
/** TODO: File Purpose */
// Created by Billy Graban
//#ifdef _SFML
#include <SFML/Audio.hpp>
#include <unordered_map>

#include ".\IAudio.h"

namespace Engine
{
	/** \class SFMLAudio */
	/** TODO: Class Purpose */
	class SFMLAudio
		: public IAudio
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SFMLAudio() {};

		/** Default Destructor */
		~SFMLAudio() {};

		//init audio system
		bool Init() override;

		//play music of the filepath, if havent been loaded, load it
		virtual bool PlayMusic(const char* filepath) override;

		//play sound of the filepath, if havent been loaded, load it
		virtual bool PlaySound(const char* filepath) override;

		//stop, resume, pause the current music
		void OperateCurrentMusic(EMusicAction action) override;

		//stop, resume, pause the current sound
		void OperateCurrentSounds(EMusicAction action) override;

		//fade in music
		virtual void FadeInMusic(const char* filepath, int loops, int ms) override;

		//fade out music in miliseconds
		virtual void FadeOutMusic(int ms) override;

		//free a loaded music
		virtual void FreeMusic(const char* filepath) override;

		//free a loaded sound
		virtual void FreeSound(const char* filepath) override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		sf::Sound* m_sfSoundArray[g_ArrayNumber];

		sf::Music* m_pMusic;

		//store the loaded music piece. 
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_pMusicMap;

		//store the loaded sound piece. 
		std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_pChunkMap;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		sf::Sound* GetAvailableSound();

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		virtual void SetMusicVolume(int volume) override;

		//set the sound volume to target value
		virtual void SetSoundVolume(const char* filepath,int volume) override;

		//get the present music volume
		virtual int GetMusicVolume() override;

		//get the sound volume
		virtual int GetSoundVolume(const char* filepath) override;

		//get the maximum value of music volume
		virtual int GetMaxVolume() override;

		//set music to the target position: position is the seconds from the beginning
		virtual void SetMusicPosition(double position) override;

		//sets up a function to be called when music playback is halted.
		virtual void SetFinishMusicCallback(void(*music_finished)()) override;

		//get the type of music
		virtual EMusicType GetMusicType(const char* filepath) override;

		//tells you if music is actively playing, or not.
		virtual bool IsMusicPlaying();

		//tells you if music is paused, or not.
		virtual bool IsMusicPaused();

		//tells you if music is fading or not.
		virtual bool IsMusicFading();
	};
}
//#endif