#pragma once
#include <vector>

class Gift
{
public:
	enum class Type
	{
		circle,
		triangle,
		none
	};
	explicit Gift(const Point2f& pos, const Color4f& colour, Type type);
	virtual ~Gift() noexcept;
	void Draw() const;
	void UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	void SetGiftPosition(const Point2f& newPos);
	void SetGravity(bool setGravity);
	void ApplyColour(const Color4f& newColour);
	bool CheckTypeCorrelates(Type type);
	Rectf ReturnObjectTriggerBoxLeft() const;
	Rectf ReturnObjectTriggerBoxRight() const;
	Color4f ReturnFrendColour() const;
	Gift::Type ReturnGiftType() const;
private:
	Type m_ObjectType{};
	Color4f m_CurrentObjectColour;
	Point2f m_PositionObject;
	Rectf m_ObjectTriggerBoxLeft{};
	Rectf m_ObjectTriggerBoxRight{};
	const float m_ObjectMeasurement{ 15.f };
	float m_ObjectVelocityY{ 0.f };
	bool m_ApplyGravity{ true };
};

