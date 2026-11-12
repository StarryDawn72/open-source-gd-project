void GJBaseGameLayer::togglePlayerVisibility(bool visible, bool player1)
{
    PlayerObject* p;

    if (player1) {
        p = this->m_player1;
    }
    else {
        if (!m_gameState.m_isDualMode) return;
        p = m_player2;
    }
    
    p->toggleVisibility(visible);
}

void GJBaseGameLayer::togglePlayerVisibility(bool visible)
{
    togglePlayerVisibility(visible, true);
    togglePlayerVisibility(visible, false);
}