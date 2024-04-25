#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "LevelManager.h"
#include <iostream>

Player::Player(const Point2f& playerPosition, LevelManager* manager)
	:m_PositionPlayer{ playerPosition }
{
	m_LevelManager = manager;
}

void Player::Draw() const
{
	utils::SetColor(m_CurrentPlayerColour);
	utils::FillRect(m_PositionPlayer, m_PlayerMeasurement, m_PlayerMeasurement);
}

void Player::HandleMovement(float elapsedSec, const Uint8* pStates)
{
	if (pStates[SDL_SCANCODE_W])
	{
		std::cout << "W is pressed" << std::endl;
		if (m_IsGrounded == true)
		{
			m_PlayerSpeed.y = 700.f;
			m_PositionPlayer.y += m_PlayerSpeed.y * elapsedSec;
		}
		m_IsGrounded = false;
	}
	if(pStates[SDL_SCANCODE_A])
	{
		std::cout << "A is pressed" << std::endl;
		m_LookingLeft = true;
		m_PlayerSpeed.x = 200.f;
		m_PositionPlayer.x -= m_PlayerSpeed.x * elapsedSec;
	}
	if(pStates[SDL_SCANCODE_D])
	{
		std::cout << "D is pressed" << std::endl;
		m_LookingLeft = false;
		m_PlayerSpeed.x = 200.f;
		m_PositionPlayer.x += m_PlayerSpeed.x * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_E])
	{
		if(m_IsConnected == false)
		{
			m_IsConnected = true;
		}
		else
		{
			m_IsConnected = false;
		}
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
	utils::HitInfo resultsLeftSide;
	utils::HitInfo resultsRightSide;
	for (int idx{ 0 }; idx < vertices.size(); idx++)
	{
		if (m_IsGrounded == true)
		{
			if (m_LookingLeft == false)
			{
				if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
				{
					m_PlayerSpeed.y = 0.f;
					m_PositionPlayer.y = resultsLeft.intersectPoint.y + 1.f;
					m_IsGrounded = true;
				}
			}
			else
			{
				if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
				{
					m_PlayerSpeed.y = 0.f;
					m_PositionPlayer.y = resultsRight.intersectPoint.y + 1.f;
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
		if(m_LookingLeft == false)
		{
			if (utils::Raycast(vertices[idx], LeftTopStart, RightTopStart, resultsRightSide))
			{
				m_PlayerSpeed.x = 0.f;
				m_PositionPlayer.x = resultsRightSide.intersectPoint.x - m_PlayerMeasurement;
			}
		}
		else
		{
			if (utils::Raycast(vertices[idx], RightTopStart, LeftTopStart, resultsLeftSide))
			{
				m_PlayerSpeed.x = 0.f;
				m_PositionPlayer.x = resultsLeftSide.intersectPoint.x;
			}
		}
	}
	if (m_IsConnected == true)
	{
		Rectf playerRect{ Rectf(m_PositionPlayer.x, m_PositionPlayer.y, m_PlayerMeasurement, m_PlayerMeasurement) };
		for (int idx{ 0 }; idx < m_LevelManager->ReturnFrendsArray().size(); idx++)
		{
			if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendTriggerBoxLeft()) == true)
			{
				m_LevelManager->ReturnFrendsArray()[idx]->SetFrendPosition(Point2f(m_PositionPlayer.x + 70.f, m_PositionPlayer.y));
			}
			if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendTriggerBoxRight()) == true)
			{
				m_LevelManager->ReturnFrendsArray()[idx]->SetFrendPosition(Point2f(m_PositionPlayer.x - 70.f, m_PositionPlayer.y));
			}
		}
	}
}

Point2f Player::GetPosition()
{
	return m_PositionPlayer;
}
