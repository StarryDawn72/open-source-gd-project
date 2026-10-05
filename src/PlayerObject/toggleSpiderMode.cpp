#define GM GameManager::sharedState()

void PlayerObject::toggleSpiderMode(bool enable, bool noEffects)
{
    if (m_isSpider == enable)
        return;

    m_isSpider = enable;
    m_gameModeChangedTime = m_totalTime;

    if (enable)
    {
        m_mainLayer->addChild(m_spiderBatchNode, 2);
        switchedToMode(GameObjectType::SpiderPortal);
        
        m_unkAngle1 = 27.0f; // TODO find name
        m_width = 27.0f;
        m_height = 27.0f;
        m_robotBoostCharge = 1.5f;

        stopRotation(false, 14);
        setRotation(0);

        int spiderFrame = std::clamp(GM->m_playerSpider.value(), 1, 69);
        std::string frameName = CCString::createWithFormat("spider_%02d_01_001.png", spiderFrame)->getCString();

        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
        m_iconSprite->setDisplayFrame(frame);

        if (m_isPlatformer && m_platformerXVelocity == 0.0)
            m_spiderSprite->runAnimation("idle01");
        else
            playDynamicSpiderRun();

        m_iconSprite->setVisible(false);

        if (!noEffects)
            spawnPortalCircle(ccc3(255, 50, 50), 50.0f);

        updatePlayerScale();
    } else {
        m_mainLayer->removeChild(m_spiderBatchNode, 0);
        m_iconSprite->setVisible(true);
        m_spiderSprite->m_animationManager->stopAnimations();

        int playerFrame = (m_playerScale != 1.0f && m_defaultMiniIcon)
                            ? 0
                            : m_maybeSavedPlayerFrame;
        
        updatePlayerFrame(playerFrame);
    }

    if (enable)
        modeDidChange();
}
