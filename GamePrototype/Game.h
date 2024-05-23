#pragma once
#include "BaseGame.h"
#include "LevelManager.h"
#include "Player.h"
#include "F.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
	void SetCurrentLevel(int level);

private:
	//MEMBERS
	Player* m_pPlayer;
	LevelManager* m_pLevelManager{ new LevelManager{GetViewPort().width, GetViewPort().height, this}};
	int m_CurrentLevel{ 1 };
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};