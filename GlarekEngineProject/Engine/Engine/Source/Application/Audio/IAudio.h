#pragma once
//FMODE
//OPENL
//stop, pause, play, offset
//sound: pitch, volume, loop

/** \file IAudio.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <memory>
#include "../../Utility/Common.h"
constexpr static int g_ArrayNumber = 8;

namespace Engine
{
	/** \class IAudio */
	/** TODO: Class Purpose */
	class IAudio
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		enum EMusicAction
		{
			kStop,
			kResume,
			kPause,
			kRewind,
		};

		enum EMusicType
		{
			kCommand,
			kWav,
			kMod,
			kMidi,
			kOgg,
			kMp3,
			kOthers
		};

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IAudio() {};

		/** Default Destructor */
		virtual ~IAudio() {};

		//init audio system
		virtual bool Init() = 0;

		//create a new audio system and return it
		static std::unique_ptr<IAudio> Create();

		//play music under the filepath, if havent been loaded, load it
		DLLEXP virtual bool PlayMusic(const char* filepath) = 0;

		//play sound under the filepath, if havent been loaded, load it
		DLLEXP virtual bool PlaySound(const char* filepath) = 0;

		//stop, resume, pause the current music
		DLLEXP virtual void OperateCurrentMusic(EMusicAction action) = 0;

		//stop, resume, pause the current sound
		DLLEXP virtual void OperateCurrentSounds(EMusicAction action) = 0;

		//fade in music
		DLLEXP virtual void FadeInMusic(const char* filepath, int loops, int ms) = 0;

		//fade out music in miliseconds
		virtual void FadeOutMusic(int ms) = 0;

		//free a loaded music
		virtual void FreeMusic(const char* filepath) = 0;

		//free a loaded sound
		virtual void FreeSound(const char* filepath) = 0;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//set the music volume to target value
		virtual void SetMusicVolume(int volume) = 0;

		//set the sound volume to target value
		virtual void SetSoundVolume(const char* filepath,int volume) = 0;

		//get the present music volume
		virtual int GetMusicVolume() = 0;

		//get the sound volume
		virtual int GetSoundVolume(const char* filepath) = 0;

		//get the maximum value of music volume
		virtual int GetMaxVolume() = 0;

		//set music to the target position 
		virtual void SetMusicPosition(double position) = 0;

		//sets up a function to be called when music playback is halted.
		virtual void SetFinishMusicCallback(void(*music_finished)()) = 0;

		//get the type of music
		virtual EMusicType GetMusicType(const char* filepath) = 0;

		//tells you if music is actively playing, or not.
		virtual bool IsMusicPlaying() = 0;

		//tells you if music is paused, or not.
		virtual bool IsMusicPaused() = 0;

		//tells you if music is fading or not.
		virtual bool IsMusicFading() = 0;
	};
}