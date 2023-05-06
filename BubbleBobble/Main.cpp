#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "BubbleBobble.h"

void load()
{
	
}

int main(int, char* []) {
	BubbleBobble bubbleBobble;
	dae::Minigin engine("../Data/");
	engine.Run([&bubbleBobble]() {bubbleBobble.Load(); });
	return 0;
}