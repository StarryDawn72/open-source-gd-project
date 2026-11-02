// @version 2.2091
/*
    Per-gamemode jump power tuning for pads.
*/
float GJBaseGameLayer::getBumpMod(PlayerObject* player, int type)
{
    GameObjectType objectType = (GameObjectType)type;

    if (objectType == GameObjectType::PinkJumpPad) {
        if (player->m_isShip)
            return 0.35f;
        else if (player->m_isBird)
            return 0.4f;
        else if (player->m_isBall)
            return 0.7f;
        else if (player->m_isSpider)
            return 0.7f;
        else
            return 0.65f; // Cube, Wave, Robot, Swing
    }
    else if (objectType == GameObjectType::RedJumpPad) {
        if (player->m_isShip)
            return player->m_playerScale >= 1.0f
                ? 0.63f  // Normal
                : 0.95f; // Mini
        else if (player->m_isBird)
            return player->m_playerScale >= 1.0f
                ? 0.6f   // Normal
                : 0.98f; // Mini
        else
            return 1.25f; // Cube, Ball, Wave, Robot, Spider, Swing
    }
    else
        return 1.0f;
}