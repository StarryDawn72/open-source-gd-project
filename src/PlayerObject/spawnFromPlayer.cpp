void PlayerObject::spawnFromPlayer(PlayerObject* player, bool flip)
{
    setVisible(true);
    setOpacity(255);
    copyAttributes(player);
    if (flip)
    {
        flipGravity(!player->m_isUpsideDown, true);
        setYVelocity(-player->getYVelocity(), 49);
    } else {
        flipGravity(player->m_isUpsideDown, true);
        setYVelocity(player->getYVelocity(), 49);
    }

    m_canJump = false;
    m_onGround = false;
    toggleVisibility(!player->m_isHidden);
    if (m_isDart)
        placeStreakPoint();
}