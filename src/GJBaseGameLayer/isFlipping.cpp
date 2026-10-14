bool GJBaseGameLayer::isFlipping()
{
    return m_gameState.m_levelFlipping != 0.0f &&
           m_gameState.m_levelFlipping != 1.0f;
}