void PlayerObject::updateDashArt()
{
    if (!m_isDashing)
        return;

	// Probably a real RobTop macro, just like the confirmed 'kTagScaleSpider'
	int kTagDashRotate = 12;

    m_iconSprite->stopActionByTag(kTagDashRotate);
    m_iconGlow->stopActionByTag(kTagDashRotate);

    m_iconSprite->setRotation(0);
    m_iconGlow->setRotation(0);

    
    float dashRingRotation = (!m_isSideways ? 0.0f : 90.0f) - m_dashAngle;

    if (m_isGoingLeft)
        dashRingRotation += 180.0;

    // setRotation(0 - angle) ensures the starting player angle matches the orb's rotation
    setRotation(dashRingRotation);

    m_dashFireSprite->stopAllActions();

    if (m_isShip){
        m_dashFireSprite->setPosition(ccp(0, 2.0f));
        m_dashFireSprite->setScaleX(1.0f);
		m_dashFireSprite->setScaleY(0.85f);
    }
    else if (m_isBird) {
        m_dashFireSprite->setPosition(ccp(0, 0));
        m_dashFireSprite->setScaleX(0.95f);
		m_dashFireSprite->setScaleY(0.9f);
    }
    else if (m_isRobot) {
        m_dashFireSprite->setPosition(ccp(1.0f, 0));
        m_dashFireSprite->setScaleX(0.9f);
        m_dashFireSprite->setScaleY(0.85f);
        m_robotSprite->runAnimation("fall_loop");
    }
    else if (m_isSpider) {
        m_dashFireSprite->setPosition(ccp(1.0f, 0));
        m_dashFireSprite->setScaleX(0.95f);
        m_dashFireSprite->setScaleY(0.8f);
        m_spiderSprite->runAnimation("fall_loop");
    }
    else {
        m_dashFireSprite->setPosition(ccp(0, 0));
        m_dashFireSprite->setScaleX(0.9f);
        m_dashFireSprite->setScaleY(0.8f);
    }
    
    if (!isFlying() && !m_isRobot && !m_isSpider) {

        // Start spinning the icon sprite when dashing

        m_iconSprite->setScale(0.9f);
        m_iconGlow->setScale(0.9f);

        float dir = (m_isSideways == m_isUpsideDown) ? 1.0f : -1.0f;
        float baseRotateSpeed = 288.0f;

        float deltaAngle = dir * baseRotateSpeed * m_gravityMod;

        if (m_isPlatformer) {

            float maxSpeed = 17.310005f;
            float min = 0.3f;
            float max = 2.0f;

            float dashLength = ccp(m_dashX, m_dashY).getLength();
            float normalizedSpeed = std::min(dashLength / maxSpeed, 1.0f);

            float mod = (normalizedSpeed * (max - min)) + min; // lerp

            deltaAngle *= mod;
        }

        // Final player dash spin: 960 degrees/sec under normal conditions
        CCRotateBy* iconRotate = CCRotateBy::create(0.3f, deltaAngle);
        CCRepeatForever* iconDashSpin = CCRepeatForever::create(iconRotate);
        iconDashSpin->setTag(kTagDashRotate);
        m_iconSprite->runAction(iconDashSpin);

        CCRotateBy* glowRotate = CCRotateBy::create(0.3f, deltaAngle);
        CCRepeatForever* glowDashSpin = CCRepeatForever::create(glowRotate);
        glowDashSpin->setTag(kTagDashRotate);
        m_iconGlow->runAction(glowDashSpin);
    }
}