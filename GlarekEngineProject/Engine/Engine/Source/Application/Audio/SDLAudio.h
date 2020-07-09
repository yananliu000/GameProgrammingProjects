#pragma once
/** \file SDLAudio.h */
/** TODO: File Purpose */
// Created by Billy Graban
#ifdef _SDL
#include <unordered_map>
#include <SDL2/SDL_mixer.h>
#include <string.h>

#include ".\IAudio.h"
namespace Engine
{
	/** \class SDLAudio */
	/** TODO: Class Purpose */
	class SDLAudio
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
		SDLAudio() {};

		/** Default Destructor */
		~SDLAudio() {};

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
		//store the loaded music piece. 
		std::unordered_map<std::string, std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>> m_pMusicMap;

		//store the loaded sound piece. 
		std::unordered_map<std::string, std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>> m_pChunkMap;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		Mix_Music* GetMusic(const char* filepath);
		Mix_Chunk* GetSound(const char* filepath);
	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//set the music volume to target value
		virtual void SetMusicVolume(int volume) override;

		//set the sound volume to target value
		virtual void SetSoundVolume(const char* filepath,int volume) override;

		//get the present music volume
		virtual int GetMusicVolume() override;

		//get the sound volume
		virtual int GetSoundVolume(const char* filepath) override;

		//get the maximum value of music volume
		virtual int GetMaxVolume() override;

		//set the muscis position: different for different format.
		//for ogg: position is seconds from the beggining of the song
		//for module: position is cast to u16 and used for the pattern number in the module
		//for mp3: position is seconds from the current position in the stream
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
#endif
