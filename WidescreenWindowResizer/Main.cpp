#include "stdio.h"
#include <Windows.h>
#include <vector>
#include "CKeyhandler.h"
#include "CMousehandler.h"

#define _WIN32_WINNT 0x050

bool isCreateWindowZone = false;
bool altState = false;
std::vector<RECT> WindowZones;


void MoveWindow(int i)
{
	if (i >= WindowZones.size())
		return;

	HWND activeHwnd = GetForegroundWindow();

	POINT pos = POINT{ WindowZones[i].left,WindowZones[i].top };
	POINT size = POINT{ WindowZones[i].right ,WindowZones[i].bottom };
	SetWindowPos(activeHwnd, HWND_TOP, pos.x, pos.y, size.x-pos.x, size.y-pos.y, SWP_ASYNCWINDOWPOS);
}

void AddWindowZone(RECT zoneRect)
{
	WindowZones.push_back(zoneRect);
}


int main()
{
	CKeyhandler keyhandler;
	CMousehandler mousehandler;

	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	

	return(0);
}