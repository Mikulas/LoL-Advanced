#include "StdAfx.hpp"
#include "Scanner.hpp"

#include <string>
#include <sstream>

Signature CScanner::signatures[] = {
	/* GAMELOOP*/		{(BYTE*) "\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x8C\x24\x00\x00\x00\x00\x5F\x5E\x5D\x64\x89\x0D\x00\x00\x00\x00\x5B\x81\xC4\x00\x00\x00\x00\xC3", "x????x????xxx????xxxxxx????xxx????x"},
	/* ORDER */			{(BYTE*) "\x55\x8B\xEC\x83\xE4\xF8\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x53\x8B\xD9\x56\xC7\x44\x24\x00\x00\x00\x00\x00\x80\x7B\x11\x00\x57\x74\x28\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxxxxxx????xx????xxxx????xx????xxxxxxx?????xxxxxxxx????x????x????x????x????"},
	/* NETWORK */		{(BYTE*) "\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x0C\x83\x3D\x00\x00\x00\x00\x00\x53\x56\x57\x75\x05\xE8\x00\x00\x00\x00\x8D\x45\x08\x50\xA1\x00\x00\x00\x00\x8D\x4C\x24\x14\x51\xE8\x00\x00\x00\x00\x83\x3D\x00\x00\x00\x00\x00\x75\x05\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x8B\x74\x24\x10\x8B\x78\x08\x83\xC0\x04\x85\xF6\x74\x04\x3B\xF0\x74\x06\xFF\x15\x00\x00\x00\x00", "xxxxxxxxxxx?????xxxxxx????xxxxx????xxxxxx????xx?????xxx????x????xxxxxxxxxxxxxxxxxxxx????"},
	/* PRINT_MSG */		{(BYTE*) "\x64\xA1\x00\x00\x00\x00\x6A\xFF\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x48\x56\x8B\xF2\x8B\x06\x85\xC0\x57\x0F\x84\x00\x00\x00\x00\x80\x78\x30\x00\x0F\x84\x00\x00\x00\x00\x8B\x76\x04\x85\xF6\x89\x44\x24\x0C\x89\x74\x24\x10\x74\x0C\x8D\x56\x04\xBF\x00\x00\x00\x00\xF0\x0F\xC1\x3A\x85\xC0\xC7\x44\x24\x00\x00\x00\x00\x00\x74\x14\x8B\x54\x24\x64\x52\x8B\x54\x24\x64\x6A\x00\x52\x51\x8B\xC8\xE8\x00\x00\x00\x00\x85\xF6\xC7\x44\x24\x00\x00\x00\x00\x00", "xx????xxx????xxxx????xxxxxxxxxxxxx????xxxxxx????xxxxxxxxxxxxxxxxxxx????xxxxxxxxx?????xxxxxxxxxxxxxxxxxx????xxxxx?????"},
	/* PRINT_ARGS */	{(BYTE*) "\xA1\x00\x00\x00\x00\x85\xC0\x56\x8B\x35\x00\x00\x00\x00\x74\x6C\x80\x78\x30\x00\x74\x66\x80\x7E\x7C\x00\x74\x04\x32\xC0\x5E\xC3", "x????xxxxx????xxxxxxxxxxxxxxxxxx"},
	/* UNIT_MNGR */		{(BYTE*) "\x83\x3D\x00\x00\x00\x00\x00\x53\x56\x57\x75\x33\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x6A\x00\xE8\x00\x00\x00\x00\x83\xC4\x18\x84\xC0\x74\x01", "xx?????xxxxxx????x????x????x????x????xxx????xxxxxxx"},
	/* PLAYER */		{(BYTE*) "\x39\x2D\x00\x00\x00\x00\xF3\x0F\x10\x05\x00\x00\x00\x00\xF3\x0F\x11\x44\x24\x28\x0F\x85\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x0F\x85\x00\x00\x00\x00\x8B\x85\x00\x00\x00\x00\x8B\x50\x08\x8D\x8D\x00\x00\x00\x00\xFF\xD2\x3D\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\xF6\x05\x88\x58\xB9\x02\x01\x75\x38\xB8\x00\x00\x00\x00\x09\x05\x00\x00\x00\x00\x6A\x00\x89\x44\x24\x38\xD9\xEE\x51\xD9\x1C\x24\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xx????xxxx????xxxxxxxx????x????xxxx????xx????xxxxx????xxx????xx????xxxxxxxxxx????xx????xxxxxxxxxxxxx????x????x????"},
	/* ZOOMHACK */		{(BYTE*) "\x76\xF3\x0F\x11\x05\x5F\x5E\xB0\x01\x5b\x59\xc2\x04\x00", "x?xxxx????xxxxxxxxx"},
};

LPMODULEENTRY32 CScanner::GetModuleInfo(DWORD dwPid)
{
    // We will get the module info of the main module
    // Since we do need the base address (which is basically 0x0040000) and the size
    static MODULEENTRY32 s_sModule; 
    HANDLE hSnapshot;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
    s_sModule.dwSize = sizeof(MODULEENTRY32);
    do
    {
        if (_wcsicmp(L"League of Legends.exe", s_sModule.szModule) == 0)
        {
            CloseHandle(hSnapshot);
            return &s_sModule;
        }
    } while(Module32Next(hSnapshot,&s_sModule));

    CloseHandle(hSnapshot);
    return NULL;
}

DWORD CScanner::FindAddr(int signatureName)
{
	Signature sig = signatures[signatureName];
	HWND hWindow = FindWindow(NULL, L"League of Legends (TM) Client");
	DWORD dwPid;
    GetWindowThreadProcessId(hWindow, &dwPid);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

	DWORD addr = SearchPattern(sig, hProcess, GetModuleInfo(dwPid));
	CloseHandle(hProcess);
	return addr;
}

std::wstring s2ws(const std::string& s)
{
 int len;
 int slength = (int)s.length() + 1;
 len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
 wchar_t* buf = new wchar_t[len];
 MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
 std::wstring r(buf);
 delete[] buf;
 return r;
}

DWORD CScanner::SearchPattern(Signature sSig, HANDLE hProcess, LPMODULEENTRY32 lpsModule)
{
	bool bFound;
    DWORD dwLen, dwRead, dwAdjust, dwParser;
    BYTE* lpbyBuffer = new BYTE[lpsModule->modBaseSize];

	dwLen = strlen(sSig.mask);

	// Read the whole main module memory to a local buffer
    ReadProcessMemory(hProcess, (void*)lpsModule->modBaseAddr, (void*)lpbyBuffer, lpsModule->modBaseSize, &dwRead);

    // We'll now parse the local buffer for our searched offset
	// i is the address we are looking for relative to modBaseAddr
    for (DWORD i = 0; i < dwRead; ++i)
    {
		// if our signature starts to match the buffer
		if (lpbyBuffer[i] == sSig.signature[0])
        {
            bFound = true;
            dwAdjust = 0; // used for INT3 skipping
            dwParser = 1;
            for (DWORD a = 1; a < dwLen; ++a)
            {
                // Skip INT3 between functions
                while (lpbyBuffer[i+a+dwAdjust] == 0xCC)
                    ++dwAdjust;

                // If the current char of the mask is "x" and the byte of the game memory is different from our searched byte,
                // then continue with the next offset
                if (sSig.mask[a] == 'x' && sSig.signature[dwParser++] != lpbyBuffer[i+a+dwAdjust])
                {
					bFound = false;
                    break;
                }
            }
            // If all bytes, following the offset, fit with the searched ones and the mask,
            // then return the address found
            if (bFound)
            {
				MessageBoxA(NULL, "Found", NULL, MB_OK);
				return (DWORD) lpsModule->modBaseAddr + i;
            }
        }
    }

	MessageBoxA(NULL, "not found", NULL, MB_OK);
	return 0; // will probably cause seg fault, we might want to force quit if received 0
}
