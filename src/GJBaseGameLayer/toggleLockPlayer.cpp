void GJBaseGameLayer::toggleLockPlayer(bool disable, bool player2)
{
    if (disable) {
        // shouldn't the parameter be called player1?
        if (player2)
            m_player1->disablePlayerControls();
        else
            m_player2->disablePlayerControls();
    } else {
        if (player2)
            m_player1->enablePlayerControls();
        else
            m_player2->enablePlayerControls();
    }
}