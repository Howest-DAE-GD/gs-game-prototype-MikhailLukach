#include "pch.h"
#include "Game.h"
#include "utils.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pPlayer = new Player{ Point2f(100.f, 100.f), m_pLevelManager };
	m_pLevelManager->SetPlayer(m_pPlayer);
	if(m_CurrentLevel == 1)
	{
		m_pLevelManager->SetLevelOne();
	}
	else if(m_CurrentLevel == 2)
	{
		m_pLevelManager->SetLevelTwo();
	}
	else if(m_CurrentLevel == 3)
	{
		m_pLevelManager->SetLevelThree();
	}
	else if (m_CurrentLevel == 4)
	{
		m_pLevelManager->SetLevelFour();
	}
	else if(m_CurrentLevel == 5)
	{
		m_pLevelManager->SetLevelFive();
	}
	//m_pLevelManager->SetLevelTwo();
	//m_pLevelManager->AddFrends(Point2f(400.f, 100.f), Color4f(1.f, 0.f, 0.f, 1.f));
	//m_pLevelManager->AddFrends(Point2f(600.f, 100.f), Color4f(1.f, 1.f, 0.f, 1.f), Gift::Type::none, Color4f(0.f, 0.f, 1.f, 1.f));
	//m_pLevelManager->AddGifts(Point2f(200.f, 100.f), Color4f(0.5f, 0.5f, 0.5f, 1.f), Gift::Type::triangle);
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_pLevelManager->UpdateCollisionFrends(m_pLevelManager->ReturnUnseperatedVertices(), elapsedSec);
	m_pPlayer->UpdateCollisions(m_pLevelManager->ReturnGroundVertices(), elapsedSec);
	m_pPlayer->UpdateCollisions(m_pLevelManager->ReturnFloatingPlatformVertices(), elapsedSec);
	m_pPlayer->UpdateCollisionsLeftRight(m_pLevelManager->ReturnGroundVertices(), elapsedSec);
	m_pPlayer->UpdateCollisionsGift(elapsedSec);
	m_pPlayer->UpdateCollisionsFinalDoor(m_pLevelManager->ReturnDoorVertices(), elapsedSec, m_pLevelManager->ReturnDoorColour());
	m_pPlayer->HandleMovement(elapsedSec, pStates);
}

void Game::Draw( ) const
{
	ClearBackground();
	m_pLevelManager->DrawHints();
	m_pLevelManager->DrawLevel();
	m_pLevelManager->DrawDoor();

	m_pLevelManager->DrawFrends();
	m_pPlayer->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_RIGHT:
		//m_pLevelManager->MoveToNewLevel();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 1.f, 1.f, 1.f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::SetCurrentLevel(int level)
{
	m_CurrentLevel = level;
	Initialize();
}
