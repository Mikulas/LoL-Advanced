#include <Windows.h>

void SetDebugPrivilege()
{
    HANDLE Htoken;
    TOKEN_PRIVILEGES tokprivls;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &Htoken))
    {
        tokprivls.PrivilegeCount = 1;
        LookupPrivilegeValue(NULL, L"SeDebugPrivilege", &tokprivls.Privileges[0].Luid);
        tokprivls.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges(Htoken, FALSE, &tokprivls, sizeof(tokprivls), NULL, NULL);
        CloseHandle(Htoken);
    }
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	SetDebugPrivilege();

	HWND hWnd = FindWindow( NULL, L"League of Legends (TM) Client" );
	DWORD dwPid;
	HANDLE hHandle;
	void* lpRemoteString;
	wchar_t szPath[] = L"Y:\\Projects\\socks-LoL-Advanced-9b54f96\\Debug\\LoLAdvanced.dll";

	if( hWnd == NULL )
	{
		MessageBox( NULL, L"Couldn't find League of Legends window!", NULL, MB_OK );
		return 1;
	}

	GetWindowThreadProcessId( hWnd, &dwPid );
	hHandle = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwPid );
	lpRemoteString = VirtualAllocEx( hHandle, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
	
	/*GetCurrentDirectory( sizeof( szPath ), szPath );
	wcscat_s( szPath, L"\\LoLAdvanced.dll" );*/

	WriteProcessMemory( hHandle, lpRemoteString, (void*)szPath, sizeof( szPath ) * 2, NULL );

	// MessageBox( NULL, szPath, L"Press OK to inject", MB_OK );
	
	HANDLE hThread = CreateRemoteThread( hHandle, NULL, 0, (LPTHREAD_START_ROUTINE) LoadLibraryW, lpRemoteString, 0, NULL );
	if (hThread == NULL)
	{
		MessageBox( NULL, L"Error creating remote thread.", NULL, MB_OK );
		return 1;
	}

	int res = WaitForSingleObject( hThread, INFINITE );
	if (res == WAIT_FAILED || res == WAIT_ABANDONED)
	{
		MessageBox( NULL, L"Thread in invalid state.", NULL, MB_OK );
		return 1;
	}

	MessageBox( NULL, szPath, L"Press OK to unload!", MB_OK );

	DWORD dwModule;
	GetExitCodeThread( hThread, &dwModule );

	CloseHandle( hThread);

	VirtualFreeEx( hHandle, lpRemoteString, 0, MEM_FREE );
	
	hThread = CreateRemoteThread( hHandle, NULL, 0, (LPTHREAD_START_ROUTINE) FreeLibrary, (void*) dwModule, 0, NULL );
	WaitForSingleObject( hThread, INFINITE );
	CloseHandle( hThread);

	CloseHandle( hHandle );

	return 0;
}