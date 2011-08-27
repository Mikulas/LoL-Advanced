#include "StdAfx.hpp"

CCore* CCore::s_lpcCore;

CCore::CCore( HMODULE hModule )
	: m_hModule( hModule ), m_bFirstLoop( true )
{
}

CCore::~CCore( void )
{
}

bool
CCore::Initialize( void )
{
	m_hWnd = FindWindow( NULL, L"League of Legends (TM) Client" );

	Game_Loop = m_cMemory.Patch<Game_Loop_t>( CMemory::Call, (DWORD) Game_Loop, (DWORD) New_Game_Loop );

	// DebugCircleManager::GetSingleton( )->AddDebugCircle( Unit::GetPlayerToon( ), 10.0f, 0xAAAAAAAA );

	return true;
}

void
CCore::GameLoop( void )
{
	//if( m_bFirstLoop == true && (* reinterpret_cast<DWORD*>( g_dwPrintArgument) ) != NULL )
	{
		char* message = "<font color='#00FF00'>LoL!Advanced</font> build";
		strcat(message, __DATE__);
		strcat(message, " <font color='#00FF00'>loaded</font>");
		Print(message);
		m_bFirstLoop = false;
	}

	m_cAutomate.OnGameLoop( );
}

void
CCore::Print( std::string szOutput ) {
	Print_Console( const_cast< char* >( szOutput.c_str( ) ), g_dwPrintArgument, false, false );
}