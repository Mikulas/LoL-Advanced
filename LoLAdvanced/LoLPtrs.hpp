#include "ObjectManager.hpp"
#include "Unit.hpp"
#include "NetApp.hpp"
#include "Scanner.hpp"

#if defined( _DEFINE_PTRS )

#define MakeVar( x, y, z ) x y = (x) z;
#define MakeFnc( ret, call, param, name, offset ) \
	name##_t name = (##name##_t) offset;
#define MakeAsm( x, y ) DWORD x = (DWORD) y;

#else

#define MakeVar( x, y, z ) extern x y;
#define MakeFnc( ret, call, param, name, offset ) \
	typedef ret##(##call##*##name##_t)##param##; \
	extern name##_t name;
#define MakeAsm( x, y ) extern DWORD x;

#endif

// Variables

MakeVar( ObjectManager*, g_lpcUnitManager, CScanner::FindAddr(SIG_UNIT_MNGR) )
MakeVar( Unit**, g_lpcLocalPlayer, CScanner::FindAddr(SIG_PLAYER) )
MakeVar( DWORD, g_dwPrintArgument, CScanner::FindAddr(SIG_PRINT_ARGS) )

// Function Pointers
MakeFnc( void, __fastcall, ( void ), Game_Loop, CScanner::FindAddr(SIG_GAMELOOP) )
MakeFnc( void, __thiscall, ( Unit* _this, DWORD dwActionType, float* lpfPos, Unit* lpcTarget, DWORD dwArg4, DWORD dwArg5, bool bUnk ), Unit_IssueOrder, CScanner::FindAddr(SIG_ORDER) )
MakeFnc( Unit*, __cdecl, ( DWORD dwNetworkId ), Unit_GetUnitByNetworkId, CScanner::FindAddr(SIG_NETWORK) )
MakeFnc( int, __fastcall, ( char* szText, DWORD dwArgument, bool bUnk1, bool bUnk2 ), Print_Console, CScanner::FindAddr(SIG_PRINT_MSG) )

#undef MakeFnc
#undef MakeVar
#undef MakeAsm
