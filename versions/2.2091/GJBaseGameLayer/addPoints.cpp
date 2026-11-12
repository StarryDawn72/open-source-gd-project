void GJBaseGameLayer::addPoints(int points)
{
    m_gameState.m_hasObtainedPoints = true;
    m_gameState.m_points += points;
}