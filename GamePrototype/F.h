#pragma once
#include <vector>
class F
{
public:
	explicit F(const Point2f& pos, const Color4f& colour);
	virtual ~F() = default;
	void Draw() const;
	void UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	Rectf ReturnFrendTriggerBoxLeft() const;
	Rectf ReturnFrendTriggerBoxRight() const;
	void SetFrendPosition(const Point2f& newPos);
private:
	Color4f m_CurrentFrendColour;
	Point2f m_PositionFrend;
	Rectf m_FrendTriggerBoxLeft{};
	Rectf m_FrendTriggerBoxRight{};
	const float m_FrendMeasurement{ 50.f };
	float m_FrendVelocityY{ 0.f };
};

