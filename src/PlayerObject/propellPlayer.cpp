void PlayerObject::propellPlayer(float yVelocity, bool noEffects, int objectType)
{
	bool& m_isJumping = m_maybeIsBoosted;
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	float& m_playerScale = m_vehicleSize;

    m_isJumping = true;
    m_onGround = false;
    m_canJump = false;
    m_isOnSlope = false;
    m_wasOnSlope = false;
    m_shouldTryPlacingCheckpoint = true;

	float scaleMod = (m_playerScale == 1.0f) ? 1.0f : 0.8f;
	
    setYVelocity((yVelocity * 16.0f * flipMod()) * scaleMod, 44);

    if (m_isBall || m_isSpider || m_isSwing)
        m_yVelocity *= 0.6f;
	
    runRotateAction(false, 7);

    if (!noEffects)
        playBumpEffect(objectType, nullptr);

    if (m_isRobot)
        m_robotSprite->runAnimation("jump_start");
    else if (m_isSpider)
        m_spiderSprite->runAnimation("fall_loop");

    activateStreak();
    m_lastGroundedPos = getPosition();
}