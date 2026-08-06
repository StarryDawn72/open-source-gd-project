void PlayerObject::playerTeleported()
{
	bool& m_onGround = m_isOnGround2; // Rename binding

    m_onGround = false;
    m_lastGroundedPos = CCPointZero;
    placeStreakPoint();
}