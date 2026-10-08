void PlayerObject::updatePlayerArt()
{
    m_mainLayer->setScaleX(reverseMod());
    
    float playerScaleY = 1.0f;
    if (!m_isSwing && !m_isBall && !isInNormalMode())
        playerScaleY = flipMod() * (m_isSideways ? -1.0f : 1.0f);
    m_mainLayer->setScaleY(playerScaleY);

    m_mainLayer->setRotation(m_isSideways ? -90.0f : 0.0f);

    float upwardAngle;
    if (m_isSideways)
        upwardAngle = m_isUpsideDown ? 180.0f : 0.0f;
    else
        upwardAngle = 90 * flipMod();
    
    m_playerGroundParticles->setAngle(upwardAngle);
    m_trailingParticles->setAngle(upwardAngle);
    m_shipClickParticles->setAngle(upwardAngle);

    CCPoint gravity = ccp(0.0f, -300 * flipMod());
    if (m_isSideways)
        gravity.swap();
    
    m_playerGroundParticles->setGravity(gravity);
    m_trailingParticles->setGravity(gravity);
    m_shipClickParticles->setGravity(gravity);

    CCPoint posVar = ccp(0.0f, 2.0f);
    if (m_isSideways) posVar.swap();

    m_trailingParticles->setPosVar(posVar);
    m_shipClickParticles->setPosVar(posVar);

    float forwardDownAngle;
    if (m_isSideways)
        forwardDownAngle = m_isUpsideDown ? 60.0f : 240.0f;
    else
        forwardDownAngle = 330 * flipMod();
    
    m_ufoClickParticles->setAngle(forwardDownAngle);
    m_robotBurstParticles->setAngle(forwardDownAngle);

    posVar = ccp(5.0f, 1.0f);
    if (m_isSideways) posVar.swap();

    m_ufoClickParticles->setPosVar(posVar);
    m_robotBurstParticles->setPosVar(posVar);

    posVar = ccp(5.0f, 1.0f);
    if (m_isRobot || m_isSpider)
        posVar = ccp(15.0f, 0.0f);

    if (m_isSideways) posVar.swap();

    m_playerGroundParticles->setPosVar(posVar);
}