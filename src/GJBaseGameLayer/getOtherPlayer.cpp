PlayerObject* GJBaseGameLayer::getOtherPlayer(PlayerObject* player)
{
    if (player->m_uniqueID == m_player1->m_uniqueID)
        return m_player2;
    return m_player1;
}