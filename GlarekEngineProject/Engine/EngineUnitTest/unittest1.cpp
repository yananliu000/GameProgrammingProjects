#include "stdafx.h"
#include "CppUnitTest.h"
#include "Math/Vector2.h"
#include <Application/System/ISystem.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(MyFirstTest)
		{
			// TODO: Your test code here
			Assert::Fail(L"Fail");
		}

		TEST_METHOD(CreateSystem)
		{
			// TODO: Your test code here
			Vector2<int> a(3, 2);
		}

		TEST_METHOD(CreateSystem1)
		{
			auto pSystem = Engine::ISystem::Create();

		}

	};

}