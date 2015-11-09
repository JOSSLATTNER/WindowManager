#include "stdio.h"
#include <Windows.h>
#include <vector>
#define _WIN32_WINNT 0x050

bool isCreateWindowZone = false;
bool altState = false;
std::vector<RECT> WindowZones;
PKBDLLHOOKSTRUCT p;
POINT pos;
RECT tmprect;

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

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;
	/*if (nCode == HC_ACTION)
	{*/
		switch (wParam)
		{
		
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:

			p = (PKBDLLHOOKSTRUCT)lParam;
			//printf("Key Down: %i\n", p->vkCode);
			if (!altState) 
			{
				if (p->vkCode == VK_LMENU)
				{
					printf("alt left Down\n");
					altState = true;
					break;
				}
				
				//MoveWindow(0);
				
			}
			if (p->vkCode == 0x51 && altState)
			{
				printf("Alt and Q Down\n");
				printf("Creat a Window Zone\n");
				isCreateWindowZone = true;
			}

			if (p->vkCode == 0x31 && altState)
			{
				printf("Move Window to Position 0\n");
				MoveWindow(0);
			}
			if (p->vkCode == 0x32 && altState)
			{
				printf("Move Window to Position 1\n");
				MoveWindow(1);
			}
			if (p->vkCode == 0x33 && altState)
			{
				printf("Move Window to Position 2\n");
				MoveWindow(2);
			}
			if (p->vkCode == 0x34 && altState)
			{
				printf("Move Window to Position 3\n");
				MoveWindow(3);
			}
			if (p->vkCode == 0x35 && altState)
			{
				printf("Move Window to Position 4\n");
				MoveWindow(4);
			}
			if (p->vkCode == 0x36 && altState)
			{
				printf("Move Window to Position 5\n");
				MoveWindow(5);
			}
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			p= (PKBDLLHOOKSTRUCT)lParam;
			if (p->vkCode == VK_LMENU && altState)
			{
				altState = false;
				break;
			}
			break;
		}
	//}
		
	return(CallNextHookEx(NULL, nCode, wParam, lParam));
}

LRESULT CALLBACK LowLevelMousProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		if (isCreateWindowZone)
		{
			GetCursorPos(&pos);
			tmprect.left = pos.x;
			tmprect.top = pos.y;

			printf("Clicked on Pos: x:%i, y:%i", pos.x, pos.y);
		}
		break;
	case WM_LBUTTONUP:
		if (isCreateWindowZone)
		{
			GetCursorPos(&pos);
			tmprect.right = pos.x;
			tmprect.bottom = pos.y;

			AddWindowZone(tmprect);
			printf("Released on Pos: x:%i, y:%i", pos.x, pos.y);
			isCreateWindowZone = false;
		}
		break;
	}
	//if(!isCreateWindowZone)
		return(CallNextHookEx(NULL, nCode, wParam, lParam));
}

int main()
{
	// Install the low-level keyboard & mouse hooks
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
	HHOOK hhkLowLevelMous = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMousProc, 0, 0);
	// Keep this app running until we're told to stop
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL))
	{
		
		//this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hhkLowLevelKybd);

	return(0);
}