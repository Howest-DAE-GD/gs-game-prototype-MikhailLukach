#pragma once
#include <vector>
#include "Gift.h"
#include "Texture.h"
class F
{
public:
	explicit F(const Point2f& pos, const Color4f& colour, Gift::Type type, const Color4f& reqGiftColour);
	virtual ~F() = default;
	void Draw() const;
	void UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec);
	bool ReturnAppeasedState() const;
	Rectf ReturnFrendTriggerBoxLeft() const;
	Rectf ReturnFrendTriggerBoxRight() const;
	Gift::Type ReturnFrendRequirement() const;
	Color4f ReturnFrendColour() const;
	Color4f ReturnFrendReqColour() const;
	void SetAppeasedState(bool isAppeased);
	void SetFrendPosition(const Point2f& newPos);
	void ReduceFrendYPosition(const float reduc);
	void TurnInvisible();
	void TurnVisible();
private:
	Gift::Type m_RequiredGift{};
	Color4f m_CurrentFrendColour;
	Color4f m_RequiredGiftColour{};
	Point2f m_PositionFrend;
	Rectf m_FrendTriggerBoxLeft{};
	Rectf m_FrendTriggerBoxRight{};
	Texture* m_pText1{ new Texture{"A triangle would be nice","ninja-gaiden-nes.ttf", 7, Color4f(0.5f, 0.5f, 0.5f, 1.f)} };
	Texture* m_pText2{ new Texture{"A circle would be nice","ninja-gaiden-nes.ttf", 7, Color4f(0.5f, 0.5f, 0.5f, 1.f)} };
	Texture* m_pText3{ new Texture{"preferably, a blue one","ninja-gaiden-nes.ttf", 7, Color4f(0.5f, 0.5f, 0.5f, 1.f)} };
	Texture* m_pText4{ new Texture{"preferably, a light blue one","ninja-gaiden-nes.ttf", 7, Color4f(0.5f, 0.5f, 0.5f, 1.f)} };
	Texture* m_pText5{ new Texture{"preferably, a light green one","ninja-gaiden-nes.ttf", 7, Color4f(0.5f, 0.5f, 0.5f, 1.f)} };
	Texture* m_pText6{ new Texture{"preferably, a pale blue one","ninja-gaiden-nes.ttf", 7, Color4f(0.5f, 0.5f, 0.5f, 1.f)} };
	const float m_FrendMeasurement{ 50.f };
	float m_FrendVelocityY{ 0.f };
	bool m_IsInvisible{ false };
	bool m_IsAppeased{ true };
};

