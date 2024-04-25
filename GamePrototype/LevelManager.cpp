#include "pch.h"
#include "LevelManager.h"
#include "utils.h"

LevelManager::LevelManager(float screenWidth, float screenHeight)
	:m_GroundVertices{},
	m_Door{},
	m_ScreenWidth{screenWidth},
	m_pArrayFrends{}
{
	std::vector<Point2f> groundLayer{};
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(screenWidth, 50.f));
	groundLayer.push_back(Point2f(screenWidth, 0.f));
	std::vector<Point2f> borderLayerLeft{};
	std::vector<Point2f> borderLayerRight{};
	//leftborder
	borderLayerLeft.push_back(Point2f(-50.f, 0.f));
	borderLayerLeft.push_back(Point2f(-50.f, screenHeight));
	borderLayerLeft.push_back(Point2f(0.f, screenHeight));
	borderLayerLeft.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayerRight.push_back(Point2f(screenWidth + 50.f, 0.f));
	borderLayerRight.push_back(Point2f(screenWidth + 50.f, screenHeight));
	borderLayerRight.push_back(Point2f(screenWidth, screenHeight));
	borderLayerRight.push_back(Point2f(screenWidth, 0.f));
	m_GroundVertices.push_back(groundLayer);
	m_GroundVertices.push_back(borderLayerLeft);
	m_GroundVertices.push_back(borderLayerRight);
}

void LevelManager::DrawLevel() const
{
	for(int idx{0}; idx < m_GroundVertices.size(); idx++)
	{
		utils::SetColor(Color4f(0.5f, 0.5f, 0.5f, 1.f));
		utils::FillPolygon(m_GroundVertices[idx]);
	}
}

void LevelManager::DrawFrends() const
{
	for(int idx{ 0 }; idx < m_pArrayFrends.size(); idx++)
	{
		m_pArrayFrends[idx]->Draw();
	}
}

void LevelManager::AddFrends(const Point2f& pos, const Color4f& colour)
{
	F* newFrend{ new F{pos, colour} };
	m_pArrayFrends.push_back(newFrend);
}

void LevelManager::UpdateCollisionFrends(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	for (int idx{ 0 }; idx < m_pArrayFrends.size(); idx++)
	{
		m_pArrayFrends[idx]->UpdateCollisions(vertices, elapsedSec);
	}
}

std::vector<std::vector<Point2f>> LevelManager::ReturnGroundVertices() const
{
	return m_GroundVertices;
}

std::vector<F*> LevelManager::ReturnFrendsArray() const
{
	return m_pArrayFrends;
}
