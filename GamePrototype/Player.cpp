#include "pch.h"
#include "Player.h"
#include "utils.h"

Player::Player(const Point2f& playerPosition)
	:m_PositionPlayer{ playerPosition }
{
}

void Player::Draw() const
{
	utils::SetColor(m_CurrentPlayerColour);
	utils::FillRect(m_PositionPlayer, m_PlayerMeasurement, m_PlayerMeasurement);
}

void Player::HandleMovement(float elapsedSec, const Uint8* pStates)
{
	if(pStates[SDL_SCANCODE_A])
	{
		m_PlayerSpeed.x = 50.f;
		m_PositionPlayer.x -= m_PlayerSpeed.x * elapsedSec;
	}
	if(pStates[SDL_SCANCODE_D])
	{
		m_PlayerSpeed.x = 50.f;
		m_PositionPlayer.x += m_PlayerSpeed.x * elapsedSec;
	}
	if(pStates[SDL_SCANCODE_W])
	{
		if (m_IsGrounded == true)
		{
			m_PlayerSpeed.y = 100.f; 
			m_PositionPlayer.y += m_PlayerSpeed.y * elapsedSec;
		}
		m_IsGrounded = false;
	}
}

void Player::UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	const float gravity{ -9.81f };
	m_PositionPlayer.y += m_PlayerSpeed.y * elapsedSec;
	m_PlayerSpeed.y += gravity;
	Point2f LeftTopStart{ Point2f(m_PositionPlayer.x, m_PositionPlayer.y + m_PlayerMeasurement) };
	Point2f LeftBottomEnd{ Point2f(m_PositionPlayer.x, m_PositionPlayer.y - 1) };
	Point2f RightTopStart{ Point2f(m_PositionPlayer.x + m_PlayerMeasurement, m_PositionPlayer.y + m_PlayerMeasurement) };
	Point2f RightBottomEnd{ Point2f(m_PositionPlayer.x + m_PlayerMeasurement, m_PositionPlayer.y - 1) };
	utils::HitInfo resultsRight;
	utils::HitInfo resultsLeft;
	for (int idx{ 0 }; idx < vertices.size(); idx++)
	{
		if (m_IsGrounded == true)
		{
			if (m_LookingLeft == false)
			{
				if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
				{
					m_PlayerSpeed.y = 0.f;
					m_PositionPlayer.y = resultsLeft.intersectPoint.y;
					m_IsGrounded = true;
				}
			}
			else
			{
				if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
				{
					m_PlayerSpeed.y = 0.f;
					m_PositionPlayer.y = resultsRight.intersectPoint.y;
					m_IsGrounded = true;
				}
			}
		}
		else
		{
			if (m_LookingLeft == false)
			{
				if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
				{
					m_PlayerSpeed.y = 0.f;
					m_PositionPlayer.y = resultsLeft.intersectPoint.y;
					m_IsGrounded = true;
				}
			}
			else
			{
				if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
				{
					m_PlayerSpeed.y = 0.f;
					m_PositionPlayer.y = resultsRight.intersectPoint.y;
					m_IsGrounded = true;
				}
			}
		}
	}
}

Point2f Player::GetPosition()
{
	return m_PositionPlayer;
}
