#define kFollowPlayerYStoreTimeInterval 0.01f

void PlayerObject::updateSpecial(float dt)
{
    m_followPlayerYTimer += dt;
    if (m_followPlayerYTimer >= kFollowPlayerYStoreTimeInterval)
    {
        m_followPlayerYTimer -= kFollowPlayerYStoreTimeInterval;
        m_followPlayerYIndex++;
    }
    m_followPlayerYPositions[m_followPlayerYIndex % 200] = m_obPosition.y;
}