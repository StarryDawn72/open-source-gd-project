// @version 2.2081
void PlayerObject::playerTeleported()
{
    m_onGround = false;
    m_lastGroundedPos = CCPointZero;
    placeStreakPoint();
}