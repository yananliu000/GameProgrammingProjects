#include <SDL2/SDL.h> //toolset
#include <SFML/Window.hpp> //toolset
#include <chrono> //time

#include "ApplicationLayer.h"
#include "../Utility/MyLogger.h"

#include "../Resource/ResourceFile.h" //resource
#include <fstream> //resource

#include <iostream> //test
using std::cout; //test
using std::endl; //test

using Engine::ApplicationLayer;
Engine::IGraphic* ApplicationLayer::m_spGraphic = nullptr;
Engine::IPhysics* ApplicationLayer::m_spPhysics = nullptr;

ApplicationLayer::ApplicationLayer():m_windowHeight(960), m_windowWidth(1200), m_windowName("WindowName")
{
	//test
	//z_stream stream;
	//inflate(&stream, 0);
}


ApplicationLayer::~ApplicationLayer()
{
}

bool Engine::ApplicationLayer::Init(char* configurationPath, char* pathToCompress, char* outputLocation)
{
	//create system
	m_pSystem = ISystem::Create();
	if (m_pSystem.get() == nullptr)
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "System Failed.");
		return false;
	}
	else
	{
		g_Logger.SetSystem(m_pSystem);
		g_Logger.write(MyLogger::LogLevel::System_Normal, "System Initialized.");
		m_pSystem->Init();
	}

	//create resource system
	std::cout << "To compress: " << pathToCompress << endl;
	cout << "Output: " << outputLocation << endl;
	auto files = m_pSystem->GetFilesInFolder(pathToCompress, true);
	Engine::ResourceFile resources;
	for (auto& e : files)
	{
		std::string resourcePath = pathToCompress + '/' + e;
		std::fstream file (resourcePath, std::ios_base::in, std::ios_base::binary);

		if (file.is_open())
		{
			file.seekg(0, file.end);
			size_t fileSize = static_cast<size_t>(file.tellg());
			file.seekg(0, file.beg);

			std::vector<char> data(fileSize);
			file.read(reinterpret_cast<char*>(data.data()), fileSize);

			resources.AddResource(e, move(data));
		}
	}
	resources.Save(outputLocation);
	//text not terminator
	//if store, read text file in binary
	//we are responsible for adding terminator
	
	//logger
	g_Logger.SetConfigurationPath(configurationPath);
	g_Logger.Init();
	g_Logger.write(MyLogger::LogLevel::System_Normal, "Logger Initialized.");

	//rand
	srand((unsigned int)time(0));

	//create game logic
	m_pGameLogic = CraeteGameLayer();
	if (m_pGameLogic.get() == nullptr)
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "GameLogic Failed.");
		return false;
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::Game_Info, "Game Initialized.");
	}

	//create window & set graphics 
	m_pWindow = m_pSystem->CreateSystemWindow(m_pGameLogic->GetGameName(), m_windowWidth, m_windowHeight);

	m_pGraphic = IGraphic::Create();
	if (!m_pGraphic || !m_pGraphic->Init(m_pWindow.get()))
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Graphics Initialization fails.");
		return false;
	}

	m_spGraphic = m_pGraphic.get();

	//keyboard && mouse
	std::unique_ptr<IKeyboard> pKeyboard = IKeyboard::Create();
	if (!pKeyboard || !pKeyboard->Init())
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Keyboard Initialization fails.");
		return false;
	}

	std::unique_ptr<IMouse> pMouse = IMouse::Create();
	if (!pMouse || !pMouse->Init(m_pGraphic.get()))
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Mouse Initialization fails.");
		return false;
	}
	m_pWindow->SetKeyboard(std::move(pKeyboard));
	m_pWindow->SetMouse(std::move(pMouse));

	//audio
	m_pAudio = IAudio::Create();
	if (!m_pAudio || !m_pAudio->Init())
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Audio Initialization fails.");
		return false;
	}

	//physics
	m_pPhysics = IPhysics::Create();
	if (!m_pPhysics)
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Physics Initialization fails.");
		return false;
	}

	if (!m_pPhysics->Init(m_pGraphic.get()))
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Physics Initialization fails.");
		return false;
	}

	m_spPhysics = m_pPhysics.get();

	//game logic
	shouldExit = false;
	m_pGameLogic->DefineFactoryComponentCreators();
	m_pGameLogic->Init(this);
	g_Logger.PrintLoggingFile();
	return true;
	
}

void Engine::ApplicationLayer::Run()
{
	auto startTime = std::chrono::high_resolution_clock::now();
	while (m_pWindow->ProcessEvents())
	{
		auto EndTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaseconds = EndTime - startTime;
		m_pGameLogic->Update(deltaseconds.count()); //duration::count() give miliseconds representation 
		m_pWindow->NextFrame();
		m_pGameLogic->EndFrame();
		startTime = EndTime;
	}
}

void Engine::ApplicationLayer::Cleanup()
{
	m_pSystem = nullptr;
	m_pGameLogic = nullptr;
}

