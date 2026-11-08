void PlayerObject::createRobot(int frame)
{
    bool robotAlreadyExists = m_robotSprite != nullptr;

    ccColor3B color, secondColor;
    std::string currentAnimation;
    bool isGlowSpriteVisible;

    if (robotAlreadyExists)
    {
        color = m_robotSprite->m_color;
        secondColor = m_robotSprite->m_secondColor;
        isGlowSpriteVisible = m_robotSprite->m_glowSprite->isVisible();
        currentAnimation = m_spiderSprite->m_animationManager->m_currentAnimation;
        m_robotBatchNode->removeMeAndCleanup();
        m_robotBatchNode->release();
        m_robotSprite = nullptr;
    }

    m_robotSprite = GJRobotSprite::create(frame);
    m_robotSprite->m_delegate = this;
    m_robotBatchNode = CCSpriteBatchNode::createWithTexture(m_robotSprite->getTexture());
    m_robotBatchNode->addChild(m_robotSprite);
    m_robotBatchNode->retain();

    if (robotAlreadyExists)
    {
        if (m_isRobot)
            m_mainLayer->addChild(m_robotBatchNode, 2);
        m_robotSprite->m_color = color;
        m_robotSprite->m_secondColor = secondColor;
        m_robotSprite->updateColors();
        m_robotSprite->updateGlowColor(m_playerColor2, false);
        m_robotSprite->runAnimation(currentAnimation);
        if (isGlowSpriteVisible)
            m_robotSprite->showGlow();
    }
}