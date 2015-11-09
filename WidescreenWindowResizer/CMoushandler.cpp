#include "CMousehandler.h"

HHOOK hhkLowLevelMous; 
POINT pos;
RECT tmprect;


LRESULT CALLBACK LowLevelMousProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		
	case WM_LBUTTONDOWN:
	
		//if (isCreateWindowZone)
		//	{
			GetCursorPos(&pos);
		//	tmprect.left = pos.x;
		//	tmprect.top = pos.y;*/

			printf("Clicked on Pos: x:%i, y:%i\n", pos.x, pos.y);
		//}
		break;
	case WM_LBUTTONUP:
		//if (isCreateWindowZone)
		//{
			GetCursorPos(&pos);
		//	tmprect.right = pos.x;
		//	tmprect.bottom = pos.y;

		//AddWindowZone(tmprect);
			printf("Released on Pos: x:%i, y:%i\n", pos.x, pos.y);
			//isCreateWindowZone = false;
		//}
		break;
	}
	//if(!isCreateWindowZone)
	return(CallNextHookEx(NULL, nCode, wParam, lParam));
}

CMousehandler::CMousehandler()
{
	hhkLowLevelMous = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMousProc, 0, 0);
}

CMousehandler::~CMousehandler()
{
	UnhookWindowsHookEx(hhkLowLevelMous);
}