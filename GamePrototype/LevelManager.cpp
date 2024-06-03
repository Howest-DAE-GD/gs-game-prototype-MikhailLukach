#include "pch.h"
#include "LevelManager.h"
#include "utils.h"
#include "Game.h"
#include "Player.h"

LevelManager::LevelManager(float screenWidth, float screenHeight, Game* game)
	:m_GroundVertices{},
	m_Door{},
	m_ScreenWidth{ screenWidth },
	m_ScreenHeight{ screenHeight },
	m_pArrayFrends{},
	m_Game{game}
{
	m_pText1 = new Texture("Press WASD to move", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText2 = new Texture("Press E to befriend and Q to ghost them :(", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText3 = new Texture("Once befriended you can combine", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText4 = new Texture("Press X to combine and Z to split", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText5 = new Texture("Become the same colour as the portal to progress", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText6 = new Texture("When near a friend:", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText7 = new Texture("Some friends will need a gift", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText8 = new Texture("When near a gift:", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText9 = new Texture("Press R to pick up and T to drop", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText10 = new Texture("Then try bringing a gift to a friend", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText11 = new Texture("Holding an object, press X to transfer colour", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_pText12 = new Texture("You can only befriend one", "ninja-gaiden-nes.ttf", 15.f, Color4f(0.5f, 0.5f, 0.5f, 1.f));
}

void LevelManager::SetLevelOne()
{
	m_GroundVertices.clear();
	m_FloatingPlatformVertices.clear();
	m_UnseperatedVertices.clear();
	m_pArrayFrends.clear();
	m_pArrayGifts.clear();
	m_CurrentLevel = 1;
	m_DoorColour = Color4f(1.f, 0.f, 1.f, 1.f);
	std::vector<Point2f> groundLayer{};
	std::vector<Point2f> borderLayerLeft{};
	std::vector<Point2f> borderLayerRight{};
	std::vector<Point2f> platformOne{};
	std::vector<Point2f> topDoor{};
	//groundBorder
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 0.f));
	//leftborder
	borderLayerLeft.push_back(Point2f(-50.f, 0.f));
	borderLayerLeft.push_back(Point2f(-50.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, 0.f));
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, 0.f));
	//topDoor
	topDoor.push_back(Point2f(m_ScreenWidth, 250.f));
	topDoor.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	//door
	m_Door.push_back(Point2f(m_ScreenWidth, 50.f));
	m_Door.push_back(Point2f(m_ScreenWidth, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 50.f));

	m_GroundVertices.push_back(groundLayer);
	m_GroundVertices.push_back(borderLayerLeft);
	m_GroundVertices.push_back(borderLayerRight);
	m_GroundVertices.push_back(topDoor);

	m_UnseperatedVertices.push_back(groundLayer);
	m_UnseperatedVertices.push_back(borderLayerLeft);
	m_UnseperatedVertices.push_back(borderLayerRight);
	m_UnseperatedVertices.push_back(topDoor);

	//addObjects
	AddFrends(Point2f(600.f, 100.f), Color4f(1.f, 0.f, 0.f, 1.f), Gift::Type::none, Color4f(1.f, 0.f, 1.f, 1.f));
}

void LevelManager::SetLevelTwo()
{
	m_GroundVertices.clear();
	m_FloatingPlatformVertices.clear();
	m_UnseperatedVertices.clear();
	m_pArrayFrends.clear();
	m_pArrayGifts.clear();
	m_CurrentLevel = 2;
	m_DoorColour = Color4f(1.f, 0.f, 1.f, 1.f);
	std::vector<Point2f> groundLayer{};
	std::vector<Point2f> borderLayerLeft{};
	std::vector<Point2f> borderLayerRight{};
	std::vector<Point2f> platformOne{};
	std::vector<Point2f> platformOneDraw{};
	std::vector<Point2f> topDoor{};
	//groundBorder
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 0.f));
	//leftborder
	borderLayerLeft.push_back(Point2f(-50.f, 0.f));
	borderLayerLeft.push_back(Point2f(-50.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, 0.f));
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, 0.f));
	//topDoor
	topDoor.push_back(Point2f(m_ScreenWidth, 250.f));
	topDoor.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	//door
	m_Door.push_back(Point2f(m_ScreenWidth, 50.f));
	m_Door.push_back(Point2f(m_ScreenWidth, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 50.f));
	//platform1
	platformOne.push_back(Point2f(100.f, 200.f));
	platformOne.push_back(Point2f(200.f, 200.f));
	platformOne.push_back(Point2f(200.f, 198.f));
	platformOne.push_back(Point2f(100.f, 198.f));

	platformOneDraw.push_back(Point2f(100.f, 200.f));
	platformOneDraw.push_back(Point2f(200.f, 200.f));
	platformOneDraw.push_back(Point2f(200.f, 150.f));
	platformOneDraw.push_back(Point2f(100.f, 150.f));

	m_GroundVertices.push_back(groundLayer);
	m_GroundVertices.push_back(borderLayerLeft);
	m_GroundVertices.push_back(borderLayerRight);
	m_FloatingPlatformVertices.push_back(platformOne);
	m_GroundVertices.push_back(topDoor);

	m_UnseperatedVertices.push_back(groundLayer);
	m_UnseperatedVertices.push_back(borderLayerLeft);
	m_UnseperatedVertices.push_back(borderLayerRight);
	m_UnseperatedVertices.push_back(platformOneDraw);
	m_UnseperatedVertices.push_back(topDoor);

	AddFrends(Point2f(600.f, 100.f), Color4f(1.f, 0.f, 0.f, 1.f), Gift::Type::triangle, Color4f(0.5f, 0.5f, 0.5f, 1.f));
	AddGifts(Point2f(150.f, 225.f), Color4f(0.5f, 0.5f, 0.5f, 1.f), Gift::Type::triangle);
}

void LevelManager::SetLevelThree()
{
	m_GroundVertices.clear();
	m_FloatingPlatformVertices.clear();
	m_UnseperatedVertices.clear();
	m_pArrayFrends.clear();
	m_pArrayGifts.clear();
	m_CurrentLevel = 3;
	m_DoorColour = Color4f(1.f, 0.f, 1.f, 1.f);
	std::vector<Point2f> groundLayer{};
	std::vector<Point2f> borderLayerLeft{};
	std::vector<Point2f> borderLayerRight{};
	std::vector<Point2f> platformOne{};
	std::vector<Point2f> platformOneDraw{};
	std::vector<Point2f> platformTwo{};
	std::vector<Point2f> platformTwoDraw{};
	std::vector<Point2f> topDoor{};

	//groundBorder
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 0.f));
	//leftborder
	borderLayerLeft.push_back(Point2f(-50.f, 0.f));
	borderLayerLeft.push_back(Point2f(-50.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, 0.f));
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, 0.f));
	//topDoor
	topDoor.push_back(Point2f(m_ScreenWidth, 250.f));
	topDoor.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	//door
	m_Door.push_back(Point2f(m_ScreenWidth, 50.f));
	m_Door.push_back(Point2f(m_ScreenWidth, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 50.f));
	//platform1
	platformOne.push_back(Point2f(200.f, 200.f));
	platformOne.push_back(Point2f(300.f, 200.f));
	platformOne.push_back(Point2f(300.f, 198.f));
	platformOne.push_back(Point2f(200.f, 198.f));

	platformOneDraw.push_back(Point2f(200.f, 200.f));
	platformOneDraw.push_back(Point2f(300.f, 200.f));
	platformOneDraw.push_back(Point2f(300.f, 150.f));
	platformOneDraw.push_back(Point2f(200.f, 150.f));

	//platform 2
	platformTwo.push_back(Point2f(400.f, 300.f));
	platformTwo.push_back(Point2f(500.f, 300.f));
	platformTwo.push_back(Point2f(500.f, 298.f));
	platformTwo.push_back(Point2f(400.f, 298.f));

	platformTwoDraw.push_back(Point2f(400.f, 300.f));
	platformTwoDraw.push_back(Point2f(500.f, 300.f));
	platformTwoDraw.push_back(Point2f(500.f, 250.f));
	platformTwoDraw.push_back(Point2f(400.f, 250.f));

	m_GroundVertices.push_back(groundLayer);
	m_GroundVertices.push_back(borderLayerLeft);
	m_GroundVertices.push_back(borderLayerRight);
	m_FloatingPlatformVertices.push_back(platformOne);
	m_FloatingPlatformVertices.push_back(platformTwo);
	m_GroundVertices.push_back(topDoor);

	m_UnseperatedVertices.push_back(groundLayer);
	m_UnseperatedVertices.push_back(borderLayerLeft);
	m_UnseperatedVertices.push_back(borderLayerRight);
	m_UnseperatedVertices.push_back(platformOneDraw);
	m_UnseperatedVertices.push_back(platformTwoDraw);
	m_UnseperatedVertices.push_back(topDoor);

	AddFrends(Point2f(600.f, 100.f), Color4f(1.f, 0.f, 0.f, 1.f), Gift::Type::triangle, Color4f(0.f, 0.f, 1.f, 1.f));
	AddGifts(Point2f(450.f, 325.f), Color4f(0.5f, 0.5f, 0.5f, 1.f), Gift::Type::triangle);
}

void LevelManager::SetLevelFour()
{
	m_GroundVertices.clear();
	m_FloatingPlatformVertices.clear();
	m_UnseperatedVertices.clear();
	m_pArrayFrends.clear();
	m_pArrayGifts.clear();
	m_CurrentLevel = 4;
	m_DoorColour = Color4f(1.f, 0.f, 1.f, 1.f);
	std::vector<Point2f> groundLayer{};
	std::vector<Point2f> borderLayerLeft{};
	std::vector<Point2f> borderLayerRight{};
	std::vector<Point2f> platformOne{};
	std::vector<Point2f> platformOneDraw{};
	std::vector<Point2f> platformTwo{};
	std::vector<Point2f> platformTwoDraw{};
	std::vector<Point2f> platformThree{};
	std::vector<Point2f> platformThreeDraw{};
	std::vector<Point2f> topDoor{};

	//groundBorder
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 0.f));
	//leftborder
	borderLayerLeft.push_back(Point2f(-50.f, 0.f));
	borderLayerLeft.push_back(Point2f(-50.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, 0.f));
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, 0.f));
	//topDoor
	topDoor.push_back(Point2f(m_ScreenWidth, 250.f));
	topDoor.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	//door
	m_Door.push_back(Point2f(m_ScreenWidth, 50.f));
	m_Door.push_back(Point2f(m_ScreenWidth, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 50.f));
	//platform1
	platformOne.push_back(Point2f(200.f, 200.f));
	platformOne.push_back(Point2f(300.f, 200.f));
	platformOne.push_back(Point2f(300.f, 198.f));
	platformOne.push_back(Point2f(200.f, 198.f));

	platformOneDraw.push_back(Point2f(200.f, 200.f));
	platformOneDraw.push_back(Point2f(300.f, 200.f));
	platformOneDraw.push_back(Point2f(300.f, 150.f));
	platformOneDraw.push_back(Point2f(200.f, 150.f));

	//platform 2
	platformTwo.push_back(Point2f(400.f, 300.f));
	platformTwo.push_back(Point2f(500.f, 300.f));
	platformTwo.push_back(Point2f(500.f, 298.f));
	platformTwo.push_back(Point2f(400.f, 298.f));

	platformTwoDraw.push_back(Point2f(400.f, 300.f));
	platformTwoDraw.push_back(Point2f(500.f, 300.f));
	platformTwoDraw.push_back(Point2f(500.f, 250.f));
	platformTwoDraw.push_back(Point2f(400.f, 250.f));

	//platform 3
	platformThree.push_back(Point2f(600.f, 400.f));
	platformThree.push_back(Point2f(700.f, 400.f));
	platformThree.push_back(Point2f(700.f, 398.f));
	platformThree.push_back(Point2f(600.f, 398.f));

	platformThreeDraw.push_back(Point2f(600.f, 400.f));
	platformThreeDraw.push_back(Point2f(700.f, 400.f));
	platformThreeDraw.push_back(Point2f(700.f, 350.f));
	platformThreeDraw.push_back(Point2f(600.f, 350.f));

	m_GroundVertices.push_back(groundLayer);
	m_GroundVertices.push_back(borderLayerLeft);
	m_GroundVertices.push_back(borderLayerRight);
	m_FloatingPlatformVertices.push_back(platformOne);
	m_FloatingPlatformVertices.push_back(platformTwo);
	m_FloatingPlatformVertices.push_back(platformThree);
	m_GroundVertices.push_back(topDoor);


	m_UnseperatedVertices.push_back(groundLayer);
	m_UnseperatedVertices.push_back(borderLayerLeft);
	m_UnseperatedVertices.push_back(borderLayerRight);
	m_UnseperatedVertices.push_back(platformOneDraw);
	m_UnseperatedVertices.push_back(platformTwoDraw);
	m_UnseperatedVertices.push_back(platformThreeDraw);
	m_UnseperatedVertices.push_back(topDoor);

	AddFrends(Point2f(600.f, 100.f), Color4f(1.f, 0.f, 0.f, 1.f), Gift::Type::triangle, Color4f(0.f, 1.f, 1.f, 1.f));
	AddFrends(Point2f(650.f, 525.f), Color4f(0.f, 1.f, 0.f, 1.f), Gift::Type::none, Color4f(0.f, 0.f, 1.f, 1.f));
	AddGifts(Point2f(450.f, 325.f), Color4f(0.5f, 0.5f, 0.5f, 1.f), Gift::Type::triangle);
}

void LevelManager::SetLevelFive()
{
	m_GroundVertices.clear();
	m_FloatingPlatformVertices.clear();
	m_UnseperatedVertices.clear();
	m_pArrayFrends.clear();
	m_pArrayGifts.clear();
	m_pPlayer->SetColour(Color4f(0.5f, 0.5f, 0.5f, 1.f));
	m_CurrentLevel = 5;
	m_DoorColour = Color4f(1.5f, 0.5f, 0.5f, 1.f);
	std::vector<Point2f> groundLayer{};
	std::vector<Point2f> borderLayerLeft{};
	std::vector<Point2f> borderLayerRight{};
	std::vector<Point2f> platformOne{};
	std::vector<Point2f> platformOneDraw{};
	std::vector<Point2f> platformTwo{};
	std::vector<Point2f> platformTwoDraw{};
	std::vector<Point2f> platformThree{};
	std::vector<Point2f> platformThreeDraw{};
	std::vector<Point2f> topDoor{};

	//groundBorder
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 50.f));
	groundLayer.push_back(Point2f(m_ScreenWidth, 0.f));
	//leftborder
	borderLayerLeft.push_back(Point2f(-50.f, 0.f));
	borderLayerLeft.push_back(Point2f(-50.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, m_ScreenHeight));
	borderLayerLeft.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, 0.f));
	borderLayerRight.push_back(Point2f(m_ScreenWidth + 50.f, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	borderLayerRight.push_back(Point2f(m_ScreenWidth, 0.f));
	//topDoor
	topDoor.push_back(Point2f(m_ScreenWidth, 250.f));
	topDoor.push_back(Point2f(m_ScreenWidth, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, m_ScreenHeight));
	topDoor.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	//door
	m_Door.push_back(Point2f(m_ScreenWidth, 50.f));
	m_Door.push_back(Point2f(m_ScreenWidth, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 250.f));
	m_Door.push_back(Point2f(m_ScreenWidth - 75.f, 50.f));
	//platform1
	platformOne.push_back(Point2f(300.f, 200.f));
	platformOne.push_back(Point2f(400.f, 200.f));
	platformOne.push_back(Point2f(400.f, 198.f));
	platformOne.push_back(Point2f(300.f, 198.f));

	platformOneDraw.push_back(Point2f(300.f, 200.f));
	platformOneDraw.push_back(Point2f(400.f, 200.f));
	platformOneDraw.push_back(Point2f(400.f, 150.f));
	platformOneDraw.push_back(Point2f(300.f, 150.f));

	//platform 2
	platformTwo.push_back(Point2f(500.f, 300.f));
	platformTwo.push_back(Point2f(600.f, 300.f));
	platformTwo.push_back(Point2f(600.f, 298.f));
	platformTwo.push_back(Point2f(500.f, 298.f));

	platformTwoDraw.push_back(Point2f(500.f, 300.f));
	platformTwoDraw.push_back(Point2f(600.f, 300.f));
	platformTwoDraw.push_back(Point2f(600.f, 250.f));
	platformTwoDraw.push_back(Point2f(500.f, 250.f));

	//platform 3
	platformThree.push_back(Point2f(100.f, 300.f));
	platformThree.push_back(Point2f(200.f, 300.f));
	platformThree.push_back(Point2f(200.f, 298.f));
	platformThree.push_back(Point2f(100.f, 298.f));

	platformThreeDraw.push_back(Point2f(100.f, 300.f));
	platformThreeDraw.push_back(Point2f(200.f, 300.f));
	platformThreeDraw.push_back(Point2f(200.f, 250.f));
	platformThreeDraw.push_back(Point2f(100.f, 250.f));

	m_GroundVertices.push_back(groundLayer);
	m_GroundVertices.push_back(borderLayerLeft);
	m_GroundVertices.push_back(borderLayerRight);
	m_FloatingPlatformVertices.push_back(platformOne);
	m_FloatingPlatformVertices.push_back(platformTwo);
	m_FloatingPlatformVertices.push_back(platformThree);
	m_GroundVertices.push_back(topDoor);


	m_UnseperatedVertices.push_back(groundLayer);
	m_UnseperatedVertices.push_back(borderLayerLeft);
	m_UnseperatedVertices.push_back(borderLayerRight);
	m_UnseperatedVertices.push_back(platformOneDraw);
	m_UnseperatedVertices.push_back(platformTwoDraw);
	m_UnseperatedVertices.push_back(platformThreeDraw);
	m_UnseperatedVertices.push_back(topDoor);

	AddFrends(Point2f(610.f, 500.f), Color4f(1.f, 0.f, 0.f, 1.f), Gift::Type::triangle, Color4f(0.5f, 0.5f, 1.5f, 1.f));
	AddFrends(Point2f(350.f, 500.f), Color4f(0.f, 1.f, 0.f, 1.f), Gift::Type::none, Color4f(0.f, 0.f, 1.f, 1.f));
	AddFrends(Point2f(550.f, 500.f), Color4f(0.f, 0.f, 1.f, 1.f), Gift::Type::circle, Color4f(0.5f, 1.5f, 0.5f, 1.f));
	AddGifts(Point2f(150.f, 500.f), Color4f(0.5f, 0.5f, 0.5f, 1.f), Gift::Type::triangle);
	AddGifts(Point2f(300.f, 60.f), Color4f(0.5f, 0.5f, 0.5f, 1.f), Gift::Type::circle);

}

void LevelManager::SetLevelSix()
{

}

void LevelManager::DrawLevel() const
{
	for(int idx{0}; idx < m_UnseperatedVertices.size(); idx++)
	{
		utils::SetColor(Color4f(0.5f, 0.5f, 0.5f, 1.f));
		utils::FillPolygon(m_UnseperatedVertices[idx]);
	}
}

void LevelManager::DrawDoor() const
{
	utils::SetColor(m_DoorColour);
	utils::FillPolygon(m_Door);
}

void LevelManager::DrawFrends() const
{
	for(int idx{ 0 }; idx < m_pArrayFrends.size(); idx++)
	{
		m_pArrayFrends[idx]->Draw();
	}
	for (int idx{ 0 }; idx < m_pArrayGifts.size(); idx++)
	{
		m_pArrayGifts[idx]->Draw();
	}
}

void LevelManager::DrawHints() const
{
	if(m_CurrentLevel == 1)
	{
		m_pText1->Draw(Point2f(5.f, 475.f));
		m_pText6->Draw(Point2f(5.f, 450.f));
		m_pText2->Draw(Point2f(5.f, 425.f));
		m_pText3->Draw(Point2f(5.f, 400.f));
		m_pText4->Draw(Point2f(5.f, 375.f));
		m_pText5->Draw(Point2f(5.f, 350.f));
	}
	else if(m_CurrentLevel == 2)
	{
		m_pText7->Draw(Point2f(5.f, 475.f));
		m_pText8->Draw(Point2f(5.f, 450.f));
		m_pText9->Draw(Point2f(5.f, 425.f));
		m_pText10->Draw(Point2f(5.f, 400.f));
	}
	else if(m_CurrentLevel == 3)
	{
		m_pText11->Draw(Point2f(5.f, 475.f));
		m_pText12->Draw(Point2f(5.f, 450.f));
	}
	else if (m_CurrentLevel == 4)
	{
		m_pText2->Draw(Point2f(5.f, 475.f));
		m_pText4->Draw(Point2f(5.f, 450.f));
		m_pText9->Draw(Point2f(5.f, 425.f));
		m_pText11->Draw(Point2f(5.f, 400.f));
		m_pText12->Draw(Point2f(5.f, 375.f));
	}
	else if (m_CurrentLevel == 5)
	{
		m_pText2->Draw(Point2f(5.f, 475.f));
		m_pText4->Draw(Point2f(5.f, 450.f));
		m_pText9->Draw(Point2f(5.f, 425.f));
		m_pText11->Draw(Point2f(5.f, 400.f));
		m_pText12->Draw(Point2f(5.f, 375.f));
	}
}

void LevelManager::RemoveGift(int index)
{
	delete m_pArrayGifts[index];
	m_pArrayGifts[index] = m_pArrayGifts.back();
	m_pArrayGifts.pop_back();
}

void LevelManager::AddFrends(const Point2f& pos, const Color4f& colour, Gift::Type type, const Color4f& reqGiftColour)
{
	F* newFrend{ new F{pos, colour, type, reqGiftColour} };
	m_pArrayFrends.push_back(newFrend);
}

void LevelManager::AddGifts(const Point2f& pos, const Color4f& colour, Gift::Type type)
{
	Gift* newGift{ new Gift{pos, colour, type} };
	m_pArrayGifts.push_back(newGift);
}

void LevelManager::UpdateCollisionFrends(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	for (int idx{ 0 }; idx < m_pArrayFrends.size(); idx++)
	{
		m_pArrayFrends[idx]->UpdateCollisions(vertices, elapsedSec);
	}
	for(int idx{0}; idx < m_pArrayGifts.size(); idx++)
	{
		m_pArrayGifts[idx]->UpdateCollisions(vertices, elapsedSec);
	}
}

void LevelManager::MoveToNewLevel()
{
	if(m_CurrentLevel != 5)
	{
		m_Game->SetCurrentLevel(m_CurrentLevel + 1);
	}
}

void LevelManager::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

std::vector<std::vector<Point2f>> LevelManager::ReturnGroundVertices() const
{
	return m_GroundVertices;
}

std::vector<std::vector<Point2f>> LevelManager::ReturnFloatingPlatformVertices() const
{
	return m_FloatingPlatformVertices;
}

std::vector<std::vector<Point2f>> LevelManager::ReturnUnseperatedVertices() const
{
	return m_UnseperatedVertices;
}

std::vector<Point2f> LevelManager::ReturnDoorVertices() const
{
	return m_Door;
}

std::vector<F*> LevelManager::ReturnFrendsArray() const
{
	return m_pArrayFrends;
}

std::vector<Gift*> LevelManager::ReturnGiftArray() const
{
	return m_pArrayGifts;
}

Color4f LevelManager::ReturnDoorColour() const
{
	return m_DoorColour;
}
