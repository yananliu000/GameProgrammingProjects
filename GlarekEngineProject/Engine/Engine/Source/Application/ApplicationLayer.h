#pragma once
#include <memory>

#include "System/ISystem.h"
#include "../Logic/IGameLayer.h"
#include "Audio/IAudio.h"
#include "View/IView.h"
#include "Graphic/IGraphic.h"
#include "Window/IWindow.h"
#include "../Game/Physics/IPhysics.h"

namespace Engine
{
	class IMouse;
	class IKeyboard;
	class ISystem;
	class IGameLayer;
	class IAudio;
	class IGraphic;
	
	class ApplicationLayer
	{
	protected:
		// window width
		const u16 m_windowWidth;

		//window height
		const u16 m_windowHeight;

		//window name
		const char* m_windowName;

		//program exit
		bool shouldExit;

		//owns logic
		std::shared_ptr<ISystem> m_pSystem;

		//own gamelayer
		std::unique_ptr<IGameLayer> m_pGameLogic;

		//owns graphics
		std::unique_ptr<IGraphic> m_pGraphic;

		//owns audio
		std::unique_ptr<IAudio> m_pAudio;

		//owns window
		std::unique_ptr<IWindow> m_pWindow;

		//owns physics
		std::unique_ptr<IPhysics> m_pPhysics;

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//global access point to the graphics system
		static IGraphic* m_spGraphic;

		//global access point to the physics system
		static IPhysics* m_spPhysics;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		//constructor
		DLLEXP ApplicationLayer();

		//destructor
		DLLEXP virtual ~ApplicationLayer();

		//init the applayer
		DLLEXP virtual bool Init(char* configurationPath, char* pathToCompress, char* outputLocation);

		//run the applayer
		DLLEXP virtual void Run();

		//clean logger and other pointers
		DLLEXP virtual void Cleanup();

		//create gameLogic(singleton and keep it as an unique pointer)
		virtual std::unique_ptr<Engine::IGameLayer> CraeteGameLayer() = 0;


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//return graphics pointer
		IGraphic* GetGraphic() { return m_pGraphic.get(); };

		//return audio pointer
		IAudio* GetAudio() { return m_pAudio.get(); };

		//return physics pointer
		IPhysics* GetPhysics() { return m_pPhysics.get(); };
		
		//return keyboar pointer
		IKeyboard* GetKeyboard() { return m_pWindow->GetKeyboard(); }

		//return mouse pointer
		IMouse* GetMouse() { return m_pWindow->GetMouse(); }

		//return window height
		u32 GetWindowHeight() const { return m_windowHeight; }

		//return window width
		u32 GetWindowWidth() const { return m_windowWidth; }
	};

}