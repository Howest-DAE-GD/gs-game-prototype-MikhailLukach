#include "pch.h"
#include "LevelManager.h"
#include "utils.h"

LevelManager::LevelManager(float screenWidth, float screenHeight)
	:m_GroundVertices{},
	m_Door{},
	m_ScreenWidth{screenWidth}
{
	std::vector<Point2f> groundLayer{};
	groundLayer.push_back(Point2f(0.f, 0.f));
	groundLayer.push_back(Point2f(0.f, 50.f));
	groundLayer.push_back(Point2f(screenWidth, 50.f));
	groundLayer.push_back(Point2f(screenWidth, 0.f));
	std::vector<Point2f> borderLayer{};
	//leftborder
	borderLayer.push_back(Point2f(-50.f, 0.f));
	borderLayer.push_back(Point2f(-50.f, screenHeight));
	borderLayer.push_back(Point2f(0.f, screenHeight));
	borderLayer.push_back(Point2f(0.f, 0.f));
	//rightborder
	borderLayer.push_back(Point2f(screenWidth + 50.f, 0.f));
	borderLayer.push_back(Point2f(screenWidth + 50.f, screenHeight));
	borderLayer.push_back(Point2f(screenWidth, screenHeight));
	borderLayer.push_back(Point2f(screenWidth, 0.f));
	m_GroundVertices.push_back(groundLayer);
}

void LevelManager::DrawLevel() const
{
	for(int idx{0}; idx < m_GroundVertices.size(); idx++)
	{
		utils::SetColor(Color4f(0.5f, 0.5f, 0.5f, 1.f));
		utils::FillPolygon(m_GroundVertices[idx]);
	}
}

std::vector<std::vector<Point2f>> LevelManager::ReturnGroundVertices() const
{
	return m_GroundVertices;
}
