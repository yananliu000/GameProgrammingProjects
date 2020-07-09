#include "IAudio.h"
#if _SFML
#include "SFMLAudio.h"
#else
#include "SDLAudio.h"
#endif

using Engine::IAudio;

std::unique_ptr<IAudio> Engine::IAudio::Create()
{
#if _SFML
		return std::make_unique<SFMLAudio>();
#else
	return std::make_unique<SDLAudio>();
#endif
	}
