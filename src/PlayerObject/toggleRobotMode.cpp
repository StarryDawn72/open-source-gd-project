#define GM GameManager::sharedState()

void PlayerObject::toggleRobotMode(bool enable, bool noEffects)
{
    if (m_isRobot == enable)
        return;

    // Rename bindings
    float& m_playerScale = m_vehicleSize;
    double& m_robotBoostCharge = m_accelerationOrSpeed;

    m_isRobot = enable;
    m_gameModeChangedTime = m_totalTime;
    
    if (enable) {
        m_mainLayer->addChild(m_robotBatchNode, 2);

        switchedToMode(GameObjectType::RobotPortal);

        m_robotBoostCharge = 1.5f;

        stopRotation(false, 12);
        setRotation(0.0f);

        int robotFrameNum = std::clamp(GM->m_playerRobot.value(), 1, 68);
        std::string robotFrameName = CCString::createWithFormat("robot_%02d_01_001.png", robotFrameNum)->getCString();

        m_iconSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(robotFrameName.c_str()));

        if (m_isPlatformer && m_platformerXVelocity == 0.0f)
            m_robotSprite->runAnimation("idle01");
        else
            m_robotSprite->runAnimation(m_currentRobotAnimation);

        m_iconSprite->setVisible(false);

        if (!noEffects)
            spawnPortalCircle(ccc3(255, 50, 50), 50.0f);

        updatePlayerScale();
    } else {
        m_mainLayer->removeChild(m_robotBatchNode, false);
        m_iconSprite->setVisible(true);
        m_robotSprite->m_animationManager->stopAnimations();

        int playerFrame = (m_playerScale != 1.0f && m_defaultMiniIcon)
                            ? 0
                            : m_maybeSavedPlayerFrame;
        
        updatePlayerFrame(playerFrame);
    }

    updatePlayerGlow();
    stopRotation(true, 13);

    if (enable)
        modeDidChange();
}
