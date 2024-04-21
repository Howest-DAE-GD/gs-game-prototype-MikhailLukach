#pragma once
#include <Vector2f.h>
#include <vector>
class Player
{
public:
	explicit Player(const Point2f& playerPosition);
	virtual ~Player() = default;
	void Draw() const;
	void HandleMovement(float elapsedSec, const Uint8* pStates);
	void UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	Point2f GetPosition();
private:
	Color4f m_CurrentPlayerColour{ Color4f(0.f, 0.f, 1.f, 1.f) };
	Point2f m_PositionPlayer;
	const float m_PlayerMeasurement{ 50.f };
	Vector2f m_PlayerSpeed{0.f, 0.f};
	bool m_IsGrounded{ true };
	bool m_LookingLeft{ false };
};

