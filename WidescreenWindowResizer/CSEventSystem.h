#pragma once

#include "CKeyhandler.h"
#include "CMousehandler.h"
#include "CWindowhandler.h"

class CEventSystem
{
private:
	CKeyhandler* m_pKeyhandler;
	CMousehandler* m_pMousehandler;
	CWindowhandler* m_pWindowhandler;

public:
	CEventSystem();
	~CEventSystem();

private:
	void HandelMessages();
};