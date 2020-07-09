#pragma once
/** \file IView.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include "../../Utility/Common.h"
namespace Engine
{
	class IGameLayer;
	class ApplicationLayer;
	/** \class IView */
	/** TODO: Class Purpose */
	class IView
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DLLEXP IView() {};

		/** Default Destructor */
		DLLEXP ~IView() {};

		//everything in the view needs updating
		DLLEXP virtual void UpdateInput() = 0;

		//Init a view
		DLLEXP virtual bool Init(ApplicationLayer* pApp) = 0;

		//DisplayTheView
		DLLEXP virtual void ViewScene() = 0;

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


	};
}