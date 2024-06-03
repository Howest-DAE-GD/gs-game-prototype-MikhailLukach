#include "pch.h"
#include "Gift.h"
#include "utils.h"

Gift::Gift(const Point2f& pos, const Color4f& colour, Type type)
	:m_PositionObject{ pos },
	m_CurrentObjectColour{colour},
	m_ObjectType{type}
{

}

Gift::~Gift() noexcept
{
}

void Gift::Draw() const
{
	//utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	//utils::DrawRect(m_ObjectTriggerBoxLeft, 2.f);
	//utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
	//utils::DrawRect(m_ObjectTriggerBoxRight, 2.f);
	utils::SetColor(m_CurrentObjectColour);
	if(m_ObjectType == Type::circle)
	{
		utils::FillEllipse(m_PositionObject.x + (m_ObjectMeasurement / 2), m_PositionObject.y + (m_ObjectMeasurement / 2)
			, m_ObjectMeasurement, m_ObjectMeasurement);
	}
	else if(m_ObjectType == Type::triangle)
	{
		utils::FillTriangle(m_PositionObject, Point2f(m_PositionObject.x + m_ObjectMeasurement, m_PositionObject.y)
			, Point2f(m_PositionObject.x + (m_ObjectMeasurement / 2), m_PositionObject.y + m_ObjectMeasurement));
	}
}

void Gift::UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	if(m_IsPickedUp != true)
	{
		if (m_ApplyGravity == true)
		{
			const float gravity{ -9.81f };
			m_PositionObject.y += m_ObjectVelocityY * elapsedSec;
			m_ObjectVelocityY += gravity;
		}
		Point2f LeftTopStart{ Point2f(m_PositionObject.x, m_PositionObject.y + m_ObjectMeasurement) };
		Point2f LeftBottomEnd{ Point2f(m_PositionObject.x, m_PositionObject.y - 1) };
		Point2f RightTopStart{ Point2f(m_PositionObject.x + m_ObjectMeasurement, m_PositionObject.y + m_ObjectMeasurement) };
		Point2f RightBottomEnd{ Point2f(m_PositionObject.x + m_ObjectMeasurement, m_PositionObject.y - 1) };
		utils::HitInfo resultsRight;
		utils::HitInfo resultsLeft;
		for (int idx{ 0 }; idx < vertices.size(); idx++)
		{
			if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
			{
				m_ObjectVelocityY = 0.f;
				m_PositionObject.y = resultsLeft.intersectPoint.y + 1.f;
			}
			else if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
			{
				m_ObjectVelocityY = 0.f;
				m_PositionObject.y = resultsLeft.intersectPoint.y + 1.f;
			}
		}
	}
	m_ObjectTriggerBoxLeft = Rectf(m_PositionObject.x - 25.f, m_PositionObject.y - 25.f, 50.f, 100.f);
	m_ObjectTriggerBoxRight = Rectf(m_PositionObject.x + 25.f, m_PositionObject.y - 25.f, 50.f, 100.f);
}

void Gift::SetGiftPosition(const Point2f& newPos)
{
	m_PositionObject = newPos;
}

void Gift::SetGravity(bool setGravity)
{
	m_ApplyGravity = setGravity;
}

void Gift::SetPickUp(bool isPickedUp)
{
	m_IsPickedUp = isPickedUp;
}

void Gift::ApplyColour(const Color4f& newColour)
{
	m_CurrentObjectColour = newColour;
}

bool Gift::CheckTypeCorrelates(Type type)
{
	if(m_ObjectType == type)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rectf Gift::ReturnObjectTriggerBoxLeft() const
{
	return m_ObjectTriggerBoxLeft;
}

Rectf Gift::ReturnObjectTriggerBoxRight() const
{
	return m_ObjectTriggerBoxRight;
}

Color4f Gift::ReturnFrendColour() const
{
	return m_CurrentObjectColour;
}

Gift::Type Gift::ReturnGiftType() const
{
	return m_ObjectType;
}


