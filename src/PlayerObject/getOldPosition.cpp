#define kFollowPlayerYStoreTimeInterval 0.01f

float PlayerObject::getOldPosition(float timeAgo)
{
    if (timeAgo <= 0.0f)
        return m_obPosition.y;

    int timeIndex = std::min((int)floorf(timeAgo / kFollowPlayerYStoreTimeInterval), 199);

    int index = m_followPlayerYIndex;
    if (timeIndex >= 0)
        index -= timeIndex;

    if (index < 0)
        index += 200;

    return m_followPlayerYPositions[index];
}