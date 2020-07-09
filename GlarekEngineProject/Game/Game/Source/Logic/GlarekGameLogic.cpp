#include <Lua/lua.hpp>

#include "Utility/MyLogger.h"
#include "GlarekGameLogic.h"
#include "../View/PlayerView.h"
#include "Application/ApplicationLayer.h"
#include "Game/Process/DelayProcess.h"
#include "Game/Process/DanceProcess.h"

bool GlarekGameLogic::Init(Engine::ApplicationLayer * pAppLayer)
{
	//create the player actor and the player view
	PlayerView* pPlayerView = new PlayerView(this);
	AddView(std::unique_ptr<PlayerView>(pPlayerView));

	if (!IGameLayer::Init(pAppLayer))
	{
		return false;
	}

	//music & sound test sdl 
	m_pAppLayer->GetAudio()->PlayMusic("Asset\\Audio\\Mp3\\Menu.mp3");
	m_pAppLayer->GetAudio()->PlaySound("Asset\\Audio\\Wav\\Click.wav");

	//music & sound test sfml
	m_pAppLayer->GetAudio()->PlayMusic("Asset\\Audio\\Ogg\\AMemoryAway.ogg");
	m_pAppLayer->GetAudio()->PlaySound("Asset\\Audio\\Wav\\Click.wav");

	//create actor test
	pPlayerView->SetPawn(CreateActor("Asset\\XML\\Actor\\RedMonster.xml"));

	//lua test
	lua_State* pstate = luaL_newstate();
	luaL_openlibs(pstate);

	//make lua aware of our functions
	lua_pushcfunction(pstate, glua::Logger_Log); //+1
	lua_setglobal(pstate, "log"); //+0

	
	luaL_dostring(pstate, "print('hello, Lua!')");
	luaL_dofile(pstate, "Asset\\Scripts\\test.lua");
	lua_getglobal(pstate, "SayHello"); // +1 if do find this, will push this to stack
	lua_pushstring(pstate, ", call Lua Function SayHello From C");

	//l state 
	//n number of return
	//r result
	//f statck offset
	lua_pcall(pstate, 1, 0, 0);
	lua_close(pstate);
	return true;
}


void GlarekGameLogic::CreateDelayProcess(std::shared_ptr<Engine::Actor> pActor)
{
	auto theProcess = std::make_shared<Engine::DelayProcess>(1.0f);
	theProcess->SetOwner(pActor);
	theProcess->SetCallback(Engine::IProcess::EState::kSucceeded, [this, pActor]()
	{
		//destroy the actor
		AddDestroyActor(pActor);
	});

	m_processManager.AttachProcess(theProcess);
}

void GlarekGameLogic::CreateMoveProcess(std::shared_ptr<Engine::Actor> pActor)
{
	/*
	std::shared_ptr<Engine::MoveProcess> theProcess;

	if (m_turnAround)
	{
		theProcess = std::make_shared<Engine::MoveProcess>(V2f(7, 7), 3.f);
	}
	else
	{
		theProcess = std::make_shared<Engine::MoveProcess>(V2f(5, 7), 3.f);
	}

	m_turnAround = !m_turnAround;
	theProcess->SetOwner(pActor);
	theProcess->SetCallback(Engine::IProcess::EState::kSucceeded, [this, pActor]()
	{
		CreateDelayProcess(pActor);
	});
	m_processManager.AttachProcess(theProcess);
	*/
}

void GlarekGameLogic::CreateDanceProcess(std::shared_ptr<Engine::Actor> pActor)
{
	auto theProcess = std::make_shared<Engine::DanceProcess>(1.f, 1.f);
	theProcess->SetOwner(pActor);
	theProcess->SetCallback(Engine::IProcess::EState::kSucceeded, [this, pActor]()
	{
		for (int i = 0; i < 2; ++i)
		{
			auto blue = CreateActor("asset\\xmlData\\actors\\BlueMonster.xml");
			CreateMoveProcess(blue);
		}
	});
	m_processManager.AttachProcess(theProcess);
}
