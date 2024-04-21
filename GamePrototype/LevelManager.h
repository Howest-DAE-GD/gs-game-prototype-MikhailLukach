#pragma once
#include <vector>
class LevelManager
{
public:
	explicit LevelManager(float screenWidth, float screenHeight);
	virtual ~LevelManager() = default;
	void DrawLevel() const;
	std::vector<std::vector<Point2f>> ReturnGroundVertices() const;
private:
	std::vector<std::vector<Point2f>> m_GroundVertices;
	std::vector<Point2f> m_Door;
	float m_ScreenWidth;
};

