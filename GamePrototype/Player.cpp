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
	m_WaitCounter += elapsedSec;
	if(m_WaitCounter >= m_MaxWait)
	{
		std::cout << "is grounded: " << m_IsGrounded << std::endl;
		std::cout << "is connected: " << m_IsConnected1 << std::endl;
		std::cout << "is already connected: " << m_IsAlreadyConencted1 << std::endl;
		std::cout << "is merged: " << m_IsMerged << std::endl;
		std::cout << "is picked up: " << m_IsPickUp << std::endl;
		std::cout << "is already picked up: " << m_IsAlreadyPickedUp << std::endl;
		m_WaitCounter -= m_MaxWait;
	}
	if (pStates[SDL_SCANCODE_W])
	{
		//std::cout << "W is pressed" << std::endl;
		if (m_IsGrounded == true)
		{
			m_PlayerSpeed.y = 700.f;
			m_PositionPlayer.y += m_PlayerSpeed.y * elapsedSec;
		}
		m_IsGrounded = false;
	}
	if(pStates[SDL_SCANCODE_A])
	{
		//std::cout << "A is pressed" << std::endl;
		m_LookingLeft = true;
		m_PlayerSpeed.x = 200.f;
		m_PositionPlayer.x -= m_PlayerSpeed.x * elapsedSec;
	}
	else if(pStates[SDL_SCANCODE_D])
	{
		//std::cout << "D is pressed" << std::endl;
		m_LookingLeft = false;
		m_PlayerSpeed.x = 200.f;
		m_PositionPlayer.x += m_PlayerSpeed.x * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_E])
	{
		//std::cout << "E is pressed" << std::endl;
		if(m_IsConnected1 != true)
		{
			m_IsConnected1 = true;
		}
	}
	if(pStates[SDL_SCANCODE_Q])
	{
		//std::cout << "Q is pressed" << std::endl;
		if (m_IsConnected1 != false && m_IsMerged != true )
		{
			m_IsConnected1 = false;
			m_IsAlreadyConencted1 = false;
			m_ConnectedFriend1->SetConnectedState(false);
			m_ConnectedFriend1 = nullptr;
		}
	}
	if(pStates[SDL_SCANCODE_X])
	{
		if(m_IsConnected1 == true && m_ConnectedFriend1 != nullptr && m_IsMerged != true)
		{
			m_ConnectedFriend1->TurnInvisible();
			m_IsMerged = true;
			m_PreviousPlayerColour = m_CurrentPlayerColour;
			SetPlayerColour(CombineColours(m_CurrentPlayerColour, m_ConnectedFriend1->ReturnFrendColour()));
		}
		if(m_IsPickUp != false && m_PickedUpGift != nullptr)
		{
			m_PickedUpGift->ApplyColour(m_CurrentPlayerColour);
			std::cout << "r: " << m_CurrentPlayerColour.r << "g: " << m_CurrentPlayerColour.g << "b: " << m_CurrentPlayerColour.b << std::endl;
		}
	}
	if(pStates[SDL_SCANCODE_Z])
	{
		if(m_IsConnected1 == true && m_ConnectedFriend1 != nullptr && m_IsMerged == true)
		{
			m_ConnectedFriend1->TurnVisible();
			m_IsMerged = false;
			m_CurrentPlayerColour = m_PreviousPlayerColour;
		}
	}
	if(pStates[SDL_SCANCODE_R])
	{
		if (m_IsPickUp != true)
		{
			m_IsPickUp = true;
		}
	}
	if(pStates[SDL_SCANCODE_T])
	{
		if (m_IsPickUp != false)
		{
			if (m_PickedUpGift != nullptr)
			{
				m_PickedUpGift->SetGravity(true);
			}
			m_IsPickUp = false;
			m_IsAlreadyPickedUp = false;
			m_PickedUpGift->SetPickUp(false);
			m_PickedUpGift = nullptr;
		}
	}
}

void Player::UpdateCollisions(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	//std::cout << m_PlayerSpeed.y << std::endl;
	Rectf playerRect{ Rectf(m_PositionPlayer.x, m_PositionPlayer.y, m_PlayerMeasurement, m_PlayerMeasurement) };
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
		if (m_IsGrounded == true )
		{
			if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
			{
				m_PlayerSpeed.y = 0.f;
				m_PositionPlayer.y = resultsLeft.intersectPoint.y + 1.f;
				m_IsGrounded = true;
			}
			else if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
			{
				m_PlayerSpeed.y = 0.f;
				m_PositionPlayer.y = resultsRight.intersectPoint.y + 1.f;
				m_IsGrounded = true;
			}
		}
		else if(m_IsGrounded == false && m_PlayerSpeed.y < 0)
		{
			if (utils::Raycast(vertices[idx], LeftTopStart, LeftBottomEnd, resultsLeft))
			{
				m_PlayerSpeed.y = 0.f;
				m_PositionPlayer.y = resultsLeft.intersectPoint.y + 1.f;
				m_IsGrounded = true;
			}
			else if (utils::Raycast(vertices[idx], RightTopStart, RightBottomEnd, resultsRight))
			{
				m_PlayerSpeed.y = 0.f;
				m_PositionPlayer.y = resultsRight.intersectPoint.y + 1.f;
				m_IsGrounded = true;
			}
		}
	}
	if (m_IsConnected1 == true && m_IsAlreadyConencted1 == false)
	{
		for (int idx{ 0 }; idx < m_LevelManager->ReturnFrendsArray().size(); idx++)
		{
			if(m_LevelManager->ReturnFrendsArray()[idx]->ReturnAppeasedState() == true)
			{
				if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendTriggerBoxLeft()) == true)
				{
					m_LevelManager->ReturnFrendsArray()[idx]->SetFrendPosition(Point2f(m_PositionPlayer.x + 50.f, m_PositionPlayer.y));
					m_ConnectedFriend1 = m_LevelManager->ReturnFrendsArray()[idx];
					m_Connected1Index = idx;
					m_IsAlreadyConencted1 = true;
				}
				else if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendTriggerBoxRight()) == true)
				{
					m_LevelManager->ReturnFrendsArray()[idx]->SetFrendPosition(Point2f(m_PositionPlayer.x - 50.f, m_PositionPlayer.y));
					m_ConnectedFriend1 = m_LevelManager->ReturnFrendsArray()[idx];
					m_Connected1Index = idx;
					m_IsAlreadyConencted1 = true;
				}
			}
			else
			{
				if(m_PickedUpGift != nullptr)
				{
					if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendTriggerBoxLeft()) == true)
					{
						if(m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendRequirement() == m_PickedUpGift->ReturnGiftType())
						{
							if(m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().r == m_PickedUpGift->ReturnFrendColour().r
								&& m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().b == m_PickedUpGift->ReturnFrendColour().b
								&& m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().g == m_PickedUpGift->ReturnFrendColour().g
								&& m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().a == m_PickedUpGift->ReturnFrendColour().a)
							{
								m_LevelManager->ReturnFrendsArray()[idx]->SetAppeasedState(true);
								m_LevelManager->RemoveGift(m_PickedUpIndex);
								m_IsPickUp = false;
								m_IsAlreadyPickedUp = false;
							}
						}
					}
					else if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendTriggerBoxRight()) == true)
					{

						if (m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendRequirement() == m_PickedUpGift->ReturnGiftType())
						{
							if (m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().r == m_PickedUpGift->ReturnFrendColour().r
								&& m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().b == m_PickedUpGift->ReturnFrendColour().b
								&& m_LevelManager->ReturnFrendsArray()[idx]->ReturnFrendReqColour().g == m_PickedUpGift->ReturnFrendColour().g)
							{
								m_LevelManager->ReturnFrendsArray()[idx]->SetAppeasedState(true);
								m_LevelManager->RemoveGift(m_PickedUpIndex);
								m_IsPickUp = false;
								m_IsAlreadyPickedUp = false;
							}
						}
					}
				}
			}
		}
	}
	else if(m_IsConnected1 == true && m_IsAlreadyConencted1 != false)
	{
		if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[m_Connected1Index]->ReturnFrendTriggerBoxLeft()) == true)
		{
			m_LevelManager->ReturnFrendsArray()[m_Connected1Index]->SetFrendPosition(Point2f(m_PositionPlayer.x + 50.f, m_PositionPlayer.y));
			m_ConnectedFriend1 = m_LevelManager->ReturnFrendsArray()[m_Connected1Index];
			m_Connected1Index = m_Connected1Index;
			m_ConnectedFriend1->SetConnectedState(true);
		}
		else if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnFrendsArray()[m_Connected1Index]->ReturnFrendTriggerBoxRight()) == true)
		{
			m_LevelManager->ReturnFrendsArray()[m_Connected1Index]->SetFrendPosition(Point2f(m_PositionPlayer.x - 50.f, m_PositionPlayer.y));
			m_ConnectedFriend1 = m_LevelManager->ReturnFrendsArray()[m_Connected1Index];
			m_Connected1Index = m_Connected1Index;
			m_ConnectedFriend1->SetConnectedState(true);
		}
	}
}

void Player::UpdateCollisionsLeftRight(const std::vector<std::vector<Point2f>>& vertices, float elapsedSec)
{
	const float gravity{ -9.81f };
	m_PositionPlayer.y += m_PlayerSpeed.y * elapsedSec;
	m_PlayerSpeed.y += gravity;
	Rectf playerRect{ Rectf(m_PositionPlayer.x, m_PositionPlayer.y, m_PlayerMeasurement, m_PlayerMeasurement) };
	Point2f LeftTopStart{ Point2f(m_PositionPlayer.x, m_PositionPlayer.y + m_PlayerMeasurement) };
	Point2f LeftBottomEnd{ Point2f(m_PositionPlayer.x, m_PositionPlayer.y - 1) };
	Point2f RightTopStart{ Point2f(m_PositionPlayer.x + m_PlayerMeasurement, m_PositionPlayer.y + m_PlayerMeasurement) };
	Point2f RightBottomEnd{ Point2f(m_PositionPlayer.x + m_PlayerMeasurement, m_PositionPlayer.y - 1) };
	utils::HitInfo resultsRightSide;
	utils::HitInfo resultsLeftSide;
	for (int idx{ 0 }; idx < vertices.size(); idx++)
	{
		if (m_LookingLeft == false)
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
}

void Player::UpdateCollisionsGift(float elapsedSec)
{
	Rectf playerRect{ Rectf(m_PositionPlayer.x, m_PositionPlayer.y, m_PlayerMeasurement, m_PlayerMeasurement) };
	if (m_IsPickUp == true && m_IsAlreadyPickedUp == false)
	{
		for (int idx{ 0 }; idx < m_LevelManager->ReturnGiftArray().size(); idx++)
		{
			if(m_LevelManager->ReturnGiftArray()[idx] != nullptr)
			{
				if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnGiftArray()[idx]->ReturnObjectTriggerBoxLeft()) == true)
				{
					m_LevelManager->ReturnGiftArray()[idx]->SetGiftPosition(Point2f(m_PositionPlayer.x + 15.f, m_PositionPlayer.y + 55.f));
					m_PickedUpGift = m_LevelManager->ReturnGiftArray()[idx];
					m_PickedUpIndex = idx;
					m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->SetGravity(false);
					m_PickedUpGift->SetPickUp(true);
					m_IsAlreadyPickedUp = true;
				}
				else if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnGiftArray()[idx]->ReturnObjectTriggerBoxRight()) == true)
				{
					m_LevelManager->ReturnGiftArray()[idx]->SetGiftPosition(Point2f(m_PositionPlayer.x - 15.f, m_PositionPlayer.y + 55.f));
					m_PickedUpGift = m_LevelManager->ReturnGiftArray()[idx];
					m_PickedUpIndex = idx;
					m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->SetGravity(false);
					m_PickedUpGift->SetPickUp(true);
					m_IsAlreadyPickedUp = true;
				}
			}
		}
	}
	else if (m_IsPickUp == true && m_IsAlreadyPickedUp != false)
	{
		if(m_LevelManager->ReturnGiftArray()[m_PickedUpIndex] != nullptr)
		{
			if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->ReturnObjectTriggerBoxLeft()) == true)
			{
				m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->SetGiftPosition(Point2f(m_PositionPlayer.x + 15.f, m_PositionPlayer.y + 55.f));
				m_PickedUpGift = m_LevelManager->ReturnGiftArray()[m_PickedUpIndex];
				m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->SetGravity(false);
				m_PickedUpGift->SetPickUp(true);
				m_PickedUpIndex = m_PickedUpIndex;
			}
			else if (utils::IsOverlapping(playerRect, m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->ReturnObjectTriggerBoxRight()) == true)
			{
				m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->SetGiftPosition(Point2f(m_PositionPlayer.x - 15.f, m_PositionPlayer.y + 55.f));
				m_PickedUpGift = m_LevelManager->ReturnGiftArray()[m_PickedUpIndex];
				m_LevelManager->ReturnGiftArray()[m_PickedUpIndex]->SetGravity(false);
				m_PickedUpGift->SetPickUp(true);
				m_PickedUpIndex = m_PickedUpIndex;
			}
		}
	}
}

void Player::UpdateCollisionsFinalDoor(const std::vector<Point2f>& vertices, float elapsedSec, const Color4f& doorColour)
{
	Point2f LeftTopStart{ Point2f(m_PositionPlayer.x, m_PositionPlayer.y + m_PlayerMeasurement) };
	Point2f LeftBottomEnd{ Point2f(m_PositionPlayer.x, m_PositionPlayer.y - 1) };
	Point2f RightTopStart{ Point2f(m_PositionPlayer.x + m_PlayerMeasurement, m_PositionPlayer.y + m_PlayerMeasurement) };
	Point2f RightBottomEnd{ Point2f(m_PositionPlayer.x + m_PlayerMeasurement, m_PositionPlayer.y - 1) };
	utils::HitInfo resultsLeftSide;
	utils::HitInfo resultsRightSide;
	if (m_LookingLeft == false)
	{
		if (utils::Raycast(vertices, LeftTopStart, RightTopStart, resultsRightSide) == true)
		{
			if(doorColour.r != m_CurrentPlayerColour.r || doorColour.b != m_CurrentPlayerColour.b 
				|| doorColour.g != m_CurrentPlayerColour.g)
			{
				m_PlayerSpeed.x = 0.f;
				m_PositionPlayer.x = resultsRightSide.intersectPoint.x - m_PlayerMeasurement;
			}
			else
			{
				std::cout << "Finished The Level!" << std::endl;
				m_LevelManager->MoveToNewLevel();
			}
		}
	}
	else
	{
		if (utils::Raycast(vertices, RightTopStart, LeftTopStart, resultsLeftSide) == true)
		{
			if (doorColour.r == m_CurrentPlayerColour.r || doorColour.b == m_CurrentPlayerColour.b
				|| doorColour.g == m_CurrentPlayerColour.g)
			{
				m_PlayerSpeed.x = 0.f;
				m_PositionPlayer.x = resultsLeftSide.intersectPoint.x;
			}
			else
			{
				m_LevelManager->MoveToNewLevel();
			}
		}
	}
}

Color4f Player::CombineColours(const Color4f& currentPlayer, const Color4f& currentFrend)
{
	float redColour{};
	float blueColour{};
	float greenColour{};
	redColour = (currentPlayer.r + currentFrend.r);
	blueColour = (currentPlayer.b + currentFrend.b);
	greenColour = (currentPlayer.g + currentFrend.g);
	std::cout << "r: " << redColour << "g: " << greenColour << "b: " << blueColour << std::endl;
	return Color4f(redColour, greenColour, blueColour, 1.f);
}

void Player::SetPlayerColour(const Color4f& newPlayerColour)
{
	m_CurrentPlayerColour = newPlayerColour;
}

void Player::SetColour(const Color4f& colour)
{
	m_CurrentPlayerColour = colour;
}

Point2f Player::GetPosition()
{
	return m_PositionPlayer;
}
