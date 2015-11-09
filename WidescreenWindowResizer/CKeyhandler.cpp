#include "CKeyhandler.h"

bool mIsCreateWindowZone = false;
bool mAltState = false;
PKBDLLHOOKSTRUCT p;

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
		printf("Key Down: %i\n", p->vkCode);
		if (!mAltState)
		{
			if (p->vkCode == VK_LMENU)
			{
				printf("alt left Down\n");
				mAltState = true;
				break;
			}
			//MoveWindow(0);

		}
		if (p->vkCode == 0x51 && mAltState)
		{
			printf("Alt and Q Down\n");
			printf("Creat a Window Zone\n");
			mIsCreateWindowZone = true;
		}

		if (p->vkCode == 0x31 && mAltState)
		{
			printf("Move Window to Position 0\n");
			//MoveWindow(0);
		}
		if (p->vkCode == 0x32 && mAltState)
		{
			printf("Move Window to Position 1\n");
			//MoveWindow(1);
		}
		if (p->vkCode == 0x33 && mAltState)
		{
			printf("Move Window to Position 2\n");
			//MoveWindow(2);
		}
		if (p->vkCode == 0x34 && mAltState)
		{
			printf("Move Window to Position 3\n");
			//MoveWindow(3);
		}
		if (p->vkCode == 0x35 && mAltState)
		{
			printf("Move Window to Position 4\n");
			//MoveWindow(4);
		}
		if (p->vkCode == 0x36 && mAltState)
		{
			printf("Move Window to Position 5\n");
			//MoveWindow(5);
		}
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		p = (PKBDLLHOOKSTRUCT)lParam;
		if (p->vkCode == VK_LMENU && mAltState)
		{
			mAltState = false;
			break;
		}
		break;
	}
	//}
	return(CallNextHookEx(NULL, nCode, wParam, lParam));
}


CKeyhandler::CKeyhandler()
{
	hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
}

CKeyhandler::~CKeyhandler()
{
	UnhookWindowsHookEx(hhkLowLevelKybd);
}


