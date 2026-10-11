void GJBaseGameLayer::updateGameplayOffsetX(int offsetX, bool staticOffset)
{
    m_gameState.m_unkInt1 = offsetX;
    m_gameState.m_unkBool2 = staticOffset;
}