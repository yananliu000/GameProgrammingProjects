#include "Application/GlarekApplicationLayer.h"

int main(int argc, char* argv[])
{
	GlarekApplicationLayer App;
	if (App.Init(argv[1], argv[2], argv[3]) == false)
	{
		App.Cleanup();
		return 1;
	}
	App.Run();
	App.Cleanup();

#if _DEBUG
	system("pause");
#endif

	return 0;

}