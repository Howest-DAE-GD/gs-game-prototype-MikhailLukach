#pragma once
#include <Vector2f.h>
#include <vector>
#include "LevelManager.h"
#include "F.h"
#include "Gift.h"
class Player
{
public:
	explicit Player(const Point2f& playerPosition, LevelManager* manager);
	virtual ~Player() = default;
	void Draw() const;
	void HandleMovement(float elapsedSec, const Uint8* pStates);
	void UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void UpdateCollisionsLeftRight(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void UpdateCollisionsGift(float elapsedSec);
	void UpdateCollisionsFinalDoor(const std::vector<Point2f>& vertices, float elapsedSec, const Color4f& doorColour);
	Color4f CombineColours(const Color4f& currentPlayer, const Color4f& currentFrend);
	void SetPlayerColour(const Color4f& newPlayerColour);
	void SetColour(const Color4f& colour);
	Point2f GetPosition();
private:
	Color4f m_CurrentPlayerColour{ Color4f(0.f, 0.f, 1.f, 1.f) };
	Color4f m_PreviousPlayerColour{};
	Point2f m_PositionPlayer;
	LevelManager* m_LevelManager;
	F* m_ConnectedFriend1{ nullptr };
	Gift* m_PickedUpGift{ nullptr };
	const float m_PlayerMeasurement{ 50.f };
	Vector2f m_PlayerSpeed{0.f, 0.f};
	int m_Connected1Index{};
	int m_PickedUpIndex{};
	float m_WaitCounter{ 0.f };
	const float m_MaxWait{ 5.f };
	bool m_IsGrounded{ true };
	bool m_LookingLeft{ false };
	bool m_IsConnected1{ false };
	bool m_IsAlreadyConencted1{ false };
	bool m_IsMerged{ false };
	bool m_IsPickUp{ false };
	bool m_IsAlreadyPickedUp{ false };
};

