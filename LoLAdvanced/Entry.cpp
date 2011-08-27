#include "StdAfx.hpp"

DWORD WINAPI DllMain( HMODULE hModule, DWORD dwReason, void* lpReserved )
{
	Beep(500, 150);
	Beep(1000, 250);

	if( dwReason == DLL_PROCESS_ATTACH )
	{
		CCore::s_lpcCore = new CCore( hModule );
		return CCore::s_lpcCore->Initialize( );
	}
	else if( dwReason == DLL_PROCESS_DETACH )
	{
		delete CCore::s_lpcCore;
	}
	return TRUE;
}
