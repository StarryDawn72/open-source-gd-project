void GJBaseGameLayer::updateGameplayOffsetY(int offsetY, bool staticOffset)
{
    m_gameState.m_unkInt2 = offsetY;
    m_gameState.m_unkBool3 = staticOffset;
}