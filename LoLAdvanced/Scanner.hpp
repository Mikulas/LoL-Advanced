#pragma once

#include <Tlhelp32.h>

#define SIG_GAMELOOP 0
#define SIG_ORDER 1
#define SIG_NETWORK 2
#define SIG_PRINT_MSG 3
#define SIG_PRINT_ARGS 4
#define SIG_UNIT_MNGR 5
#define SIG_PLAYER 6
#define SIG_ZOOMHACK 7

typedef struct {
	BYTE* signature;
    char* mask;
} Signature;

class CScanner
{
public:
	static DWORD FindAddr(int);

private:
	static DWORD SearchPattern(Signature, HANDLE, LPMODULEENTRY32);
	static Signature signatures[];
	static LPMODULEENTRY32 GetModuleInfo(DWORD);
};
