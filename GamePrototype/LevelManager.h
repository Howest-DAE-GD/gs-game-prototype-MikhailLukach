#pragma once
#include <vector>
#include "F.h"
class LevelManager
{
public:
	explicit LevelManager(float screenWidth, float screenHeight);
	virtual ~LevelManager() = default;
	void DrawLevel() const;
	void DrawFrends() const;
	void AddFrends(const Point2f& pos, const Color4f& colour);
	void UpdateCollisionFrends(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	std::vector<std::vector<Point2f>> ReturnGroundVertices() const;
	std::vector<F*> ReturnFrendsArray() const;
private:
	std::vector<std::vector<Point2f>> m_GroundVertices;
	std::vector<Point2f> m_Door;
	std::vector<F*> m_pArrayFrends;
	float m_ScreenWidth;
};

