void PlayerObject::copyAttributes(PlayerObject* src) {
    m_isRespawning = true;
    m_totalTime = src->m_totalTime;
    m_position = src->m_position;
    setPosition(src->getPosition());
    m_shipRotation = src->m_shipRotation;

    flipGravity(src->m_isUpsideDown, true);
    doReversePlayer(src->m_isGoingLeft);

    toggleFlyMode(src->m_isShip, false);
    toggleBirdMode(src->m_isBird, false);
    toggleRollMode(src->m_isBall, false);
    toggleDartMode(src->m_isDart, false);
    toggleRobotMode(src->m_isRobot, false);
    toggleSpiderMode(src->m_isSpider, false);
    toggleSwingMode(src->m_isSwing, false);
    updateTimeMod(src->m_playerSpeed, false);
    togglePlayerScale(src->m_vehicleSize != 1.0f, false);

    setYVelocity(src->getYVelocity(), 48);
    m_isRespawning = false;
    m_holdingJump = src->m_holdingJump;
    m_isJumpUnused = src->m_isJumpUnused;
}