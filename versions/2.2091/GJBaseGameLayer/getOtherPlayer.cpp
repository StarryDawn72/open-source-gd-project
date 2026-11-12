PlayerObject* GJBaseGameLayer::getOtherPlayer(PlayerObject* player)
{
    return (player->m_uniqueID == m_player1->m_uniqueID) ? m_player2 : m_player1;
}