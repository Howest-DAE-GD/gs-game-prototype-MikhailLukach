#include "pch.h"
#include "F.h"
#include "utils.h"

F::F(const Point2f& pos, const Color4f& colour)
	:m_PositionFrend(pos),
	m_CurrentFrendColour(colour)
{
}

void F::Draw() const
{
	utils::SetColor(m_CurrentFrendColour);
	utils::FillRect(m_PositionFrend, m_FrendMeasurement, m_FrendMeasurement);
	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	utils::DrawRect(m_FrendTriggerBoxLeft, 2.f);
	utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
	utils::DrawRect(m_FrendTriggerBoxRight, 2.f);
}

void F::UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	const float gravity{ -9.81f };
	m_PositionFrend.y += m_FrendVelocityY * elapsedSec;
	m_FrendVelocityY += gravity;
	Point2f LeftTopStart{ Point2f(m_PositionFrend.x, m_PositionFrend.y + m_FrendMeasurement) };
	Point2f LeftBottomEnd{ Point2f(m_PositionFrend.x, m_PositionFrend.y - 1) };
	Point2f RightTopStart{ Point2f(m_PositionFrend.x + m_FrendMeasurement, m_PositionFrend.y + m_FrendMeasurement) };
	Point2f RightBottomEnd{ Point2f(m_PositionFrend.x + m_FrendMeasurement, m_PositionFrend.y - 1) };
	utils::HitInfo resultsRight;
	utils::HitInfo resultsLeft;
	for (int idx{ 0 }; idx < vertices.size(); idx++)
	{
		if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
		{
			m_FrendVelocityY = 0.f;
			m_PositionFrend.y = resultsLeft.intersectPoint.y + 1.f;
		}
		else if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
		{
			m_FrendVelocityY = 0.f;
			m_PositionFrend.y = resultsLeft.intersectPoint.y + 1.f;
		}
	}
	m_FrendTriggerBoxLeft = Rectf(m_PositionFrend.x - 50.f, m_PositionFrend.y, 50.f, 50.f);
	m_FrendTriggerBoxRight = Rectf(m_PositionFrend.x + 50.f, m_PositionFrend.y, 50.f, 50.f);
}

Rectf F::ReturnFrendTriggerBoxLeft() const
{
	return m_FrendTriggerBoxLeft;
}

Rectf F::ReturnFrendTriggerBoxRight() const
{
	return m_FrendTriggerBoxRight;
}

void F::SetFrendPosition(const Point2f& newPos)
{
	m_PositionFrend = newPos;
}


