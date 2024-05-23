#pragma once
#include <vector>
#include "F.h"
#include "Texture.h"
#include "Gift.h"
class Game;
class Player;
class LevelManager
{
public:
	explicit LevelManager(float screenWidth, float screenHeight, Game* game);
	virtual ~LevelManager() = default;
	void SetLevelOne();
	void SetLevelTwo();
	void SetLevelThree();
	void SetLevelFour();
	void SetLevelFive();
	void SetLevelSix();
	void DrawLevel() const;
	void DrawDoor() const;
	void DrawFrends() const;
	void DrawHints() const;
	void RemoveGift(int index);
	void AddFrends(const Point2f& pos, const Color4f& colour, Gift::Type type, const Color4f& reqGiftColour);
	void AddGifts(const Point2f& pos, const Color4f& colour, Gift::Type type);
	void UpdateCollisionFrends(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void MoveToNewLevel();
	void SetPlayer(Player* player);
	std::vector<std::vector<Point2f>> ReturnGroundVertices() const;
	std::vector<std::vector<Point2f>> ReturnFloatingPlatformVertices() const;
	std::vector<std::vector<Point2f>> ReturnUnseperatedVertices() const;
	std::vector<Point2f> ReturnDoorVertices() const;
	std::vector<F*> ReturnFrendsArray() const;
	std::vector<Gift*> ReturnGiftArray() const;
	Game* m_Game{};
	Player* m_pPlayer{};
	Color4f ReturnDoorColour() const;
private:
	std::vector<std::vector<Point2f>> m_GroundVertices;
	std::vector<std::vector<Point2f>> m_FloatingPlatformVertices;
	std::vector<std::vector<Point2f>> m_UnseperatedVertices;
	std::vector<Point2f> m_Door;
	std::vector<F*> m_pArrayFrends;
	std::vector<Gift*> m_pArrayGifts;
	Texture* m_pText1;
	Texture* m_pText2;
	Texture* m_pText3; 
	Texture* m_pText4;
	Texture* m_pText5;
	Texture* m_pText6;
	Texture* m_pText7;
	Texture* m_pText8;
	Texture* m_pText9;
	Texture* m_pText10;
	Texture* m_pText11;
	Texture* m_pText12;
	Color4f m_DoorColour{};
	float m_ScreenWidth;
	float m_ScreenHeight;
	int m_CurrentLevel{ };
};

