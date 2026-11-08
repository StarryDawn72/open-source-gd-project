void PlayerObject::copyAttributes(PlayerObject* player) {
    m_isRespawning = true;
    m_totalTime = player->m_totalTime;
    m_position = player->m_position;
    setPosition(player->getPosition());
    m_shipRotation = player->m_shipRotation;

    flipGravity(player->m_isUpsideDown, true);
    doReversePlayer(player->m_isGoingLeft);

    toggleFlyMode(player->m_isShip, false);
    toggleBirdMode(player->m_isBird, false);
    toggleRollMode(player->m_isBall, false);
    toggleDartMode(player->m_isDart, false);
    toggleRobotMode(player->m_isRobot, false);
    toggleSpiderMode(player->m_isSpider, false);
    toggleSwingMode(player->m_isSwing, false);
    updateTimeMod(player->m_playerSpeed, false);
    togglePlayerScale(player->m_vehicleSize != 1.0f, false);

    setYVelocity(player->getYVelocity(), 48);
    m_isRespawning = false;
    m_holdingJump = player->m_holdingJump;
    m_isJumpUnused = player->m_isJumpUnused;
}
