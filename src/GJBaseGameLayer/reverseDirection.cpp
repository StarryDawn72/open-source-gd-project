void GJBaseGameLayer::reverseDirection(EffectGameObject* object)
{
    m_player1->reversePlayer(nullptr);
    if (m_gameState.m_isDualMode)
        m_player2->reversePlayer(nullptr);
}