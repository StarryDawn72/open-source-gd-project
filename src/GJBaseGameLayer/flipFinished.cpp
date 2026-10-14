void GJBaseGameLayer::flipFinished()
{
    m_player1->levelFlipFinished();
    if (m_gameState.m_isDualMode)
        m_player2->levelFlipFinished();
    m_gameState.m_unkBool11 = false;
    m_gameState.m_unkBool12 = false;
}