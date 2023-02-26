#include "Application.h"

#if !defined(AppWidth) && !defined(AppHeight)
	#define AppWidth 1280
	#define AppHeight 720
	#define AppTitle "Listboard"
#endif

int main()
{
	Application App(AppWidth, AppHeight, AppTitle);

	App.run();

	return 0;
}
