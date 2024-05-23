#include "pch.h"
#include "F.h"
#include "utils.h"

F::F(const Point2f& pos, const Color4f& colour, Gift::Type type, const Color4f& reqGiftColour)
	:m_PositionFrend(pos),
	m_CurrentFrendColour(colour),
	m_RequiredGift(type),
	m_RequiredGiftColour(reqGiftColour)
{
	if(type == Gift::Type::none)
	{
		m_IsAppeased = true;
	}
	else
	{
		m_IsAppeased = false;
	}
}

void F::Draw() const
{
	utils::SetColor(m_CurrentFrendColour);
	utils::FillRect(m_PositionFrend, m_FrendMeasurement, m_FrendMeasurement);
	//utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	//utils::DrawRect(m_FrendTriggerBoxLeft, 2.f);
	//utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
	//utils::DrawRect(m_FrendTriggerBoxRight, 2.f);
	if(m_IsAppeased != true)
	{
		if (m_RequiredGift == Gift::Type::triangle)
		{
			if (m_RequiredGiftColour.r == 0.f && m_RequiredGiftColour.g == 0.f && m_RequiredGiftColour.b == 1.f)
			{
				m_pText3->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			else if (m_RequiredGiftColour.r == 0.f && m_RequiredGiftColour.g == 1.f && m_RequiredGiftColour.b == 1.f)
			{
				m_pText4->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			else if(m_RequiredGiftColour.r == 0.5f && m_RequiredGiftColour.g == 1.5f && m_RequiredGiftColour.b == 0.5f)
			{
				m_pText5->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			else if (m_RequiredGiftColour.r == 0.5f && m_RequiredGiftColour.g == 0.5f && m_RequiredGiftColour.b == 1.5f)
			{
				m_pText6->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			m_pText1->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 68.f));

		}
		else if(m_RequiredGift == Gift::Type::circle)
		{
			if (m_RequiredGiftColour.r == 0.f && m_RequiredGiftColour.g == 0.f && m_RequiredGiftColour.b == 1.f)
			{
				m_pText3->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			else if (m_RequiredGiftColour.r == 0.f && m_RequiredGiftColour.g == 1.f && m_RequiredGiftColour.b == 1.f)
			{
				m_pText4->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			else if (m_RequiredGiftColour.r == 0.5f && m_RequiredGiftColour.g == 1.5f && m_RequiredGiftColour.b == 0.5f)
			{
				m_pText5->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			else if (m_RequiredGiftColour.r == 0.5f && m_RequiredGiftColour.g == 0.5f && m_RequiredGiftColour.b == 1.5f)
			{
				m_pText6->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 55.f));
			}
			m_pText2->Draw(Point2f(m_PositionFrend.x - 50.f, m_PositionFrend.y + 68.f));
		}
	}
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

bool F::ReturnAppeasedState() const
{
	return m_IsAppeased;
}

Rectf F::ReturnFrendTriggerBoxLeft() const
{
	return m_FrendTriggerBoxLeft;
}

Rectf F::ReturnFrendTriggerBoxRight() const
{
	return m_FrendTriggerBoxRight;
}

Gift::Type F::ReturnFrendRequirement() const
{
	return m_RequiredGift;
}

Color4f F::ReturnFrendColour() const
{
	return m_CurrentFrendColour;
}

Color4f F::ReturnFrendReqColour() const
{
	return m_RequiredGiftColour;
}

void F::SetAppeasedState(bool isAppeased)
{
	m_IsAppeased = isAppeased;
}

void F::SetFrendPosition(const Point2f& newPos)
{
	m_PositionFrend = newPos;
}

void F::ReduceFrendYPosition(const float minReduc)
{
	m_PositionFrend.y += minReduc;
}

void F::TurnInvisible()
{
	if(m_IsInvisible != true)
	{
		m_CurrentFrendColour.a = 0.f;
		m_IsInvisible = true;
	}
}

void F::TurnVisible()
{
	if (m_IsInvisible != false)
	{
		m_CurrentFrendColour.a = 1.f;
		m_IsInvisible = false;
	}
}


