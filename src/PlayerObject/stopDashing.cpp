#define kPlayerCommandStopSlide 543

// idk what to name this
#define kDashingLength 17.31f

void PlayerObject::stopDashing() {
    if (!m_isDashing)
        return;

    m_isDashing = false;
    m_lastLandTime = 0.0;

    if (m_isPlatformer && m_dashRing) {
        updatePlayerForce(ccp(m_dashX, m_dashY) * m_dashRing->m_endBoost, false);
        if (m_dashRing->m_stopSlide)
            handlePlayerCommand(kPlayerCommandStopSlide);
    }

    m_dashRing = nullptr;
    m_dashFireSprite->setVisible(false);

    if (m_playEffects && !m_isRespawning) {
        CCSprite* dashEffect = CCSprite::createWithSpriteFrameName("playerDash2_001.png");
        dashEffect->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
        PL->m_objectLayer->addChild(dashEffect, 40);

        CCSprite* dashEffectOutline = CCSprite::createWithSpriteFrameName("playerDash2_outline_001.png");
        dashEffect->addChild(dashEffectOutline, 1);
        dashEffectOutline->setPosition(dashEffect->getScaledContentSize() * 0.5f);
        dashEffectOutline->setOpacity(150);

        dashEffect->setPosition(getPosition() + m_dashFireSprite->getPosition());
        dashEffect->setScaleX(m_dashFireSprite->getScaleX() * m_playerScale);
        dashEffect->setScaleY(m_dashFireSprite->getScaleY() * m_playerScale);
        dashEffect->setColor(m_dashFireSprite->getColor());
        dashEffect->setRotation(-m_dashAngle);
        
        // Normally, it is CCSequence::create() but I'm having trouble with the variadic args
        // This is the same thing anyway
        CCSequence* sequence = CCSequence::createWithTwoActions(
            CCScaleTo::create(0.2f, dashEffect->getScaleX() * 0.2f, dashEffect->getScaleY() * 0.2f),
            CCCallFunc::create(dashEffect, callfunc_selector(CCSprite::removeMeAndCleanup))
        );

        dashEffect->runAction(sequence);

        dashEffect->runAction(CCMoveBy::create(0.2f, ccp(-20.0f, 0.0f)));
        dashEffect->runAction(CCFadeTo::create(0.2f, 0));
        dashEffectOutline->runAction(CCFadeTo::create(0.2f, 0));
    }

    m_dashParticles->stopSystem();

    if (!isFlying() && !m_isRobot && !m_isSpider) {
        float iconSpriteRotation = m_iconSprite->getRotation();

        m_iconSprite->setScale(1.0f);
        m_iconSprite->stopAllActions();
        m_iconSprite->setRotation(0.0f);

        m_iconGlow->setScale(1.0f);
        m_iconGlow->stopAllActions();
        m_iconGlow->setRotation(0.0f);

        setRotation(iconSpriteRotation);

        if (m_isPlatformer) {
            float length = CCPoint(m_dashX, m_dashY).getLength();
            float rotationSpeed;
            if (length > kDashingLength)
                rotationSpeed = 2.0f;
            else
                rotationSpeed = length / kDashingLength * 1.5f + 0.5f;
            runNormalRotation(true, rotationSpeed);
        }
    }

    if (m_isBall && m_isPlatformer)
        stopRotation(false, 5);
    if (m_isBall)
        runBallRotation(1.0f);

    if (m_onGround) {
        if (m_isRobot)
            m_robotSprite->runAnimation(m_currentRobotAnimation);
        else if (m_isSpider)
            playDynamicSpiderRun();
    }

    if (m_gameLayer)
        gameEventTriggered((int)GJGameEvent::DashStop, 0);
}