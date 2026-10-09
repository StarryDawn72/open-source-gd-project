void PlayerObject::createSpider(int frame)
{
    bool spiderAlreadyExists = m_spiderSprite != nullptr;

    ccColor3B color;
    ccColor3B secondColor;
    
    std::string currentAnimation;
    bool isGlowSpriteVisible;

    if (spiderAlreadyExists)
    {
        color = m_spiderSprite->m_color;
        secondColor = m_spiderSprite->m_secondColor;
        isGlowSpriteVisible = m_spiderSprite->m_glowSprite->isVisible();
        currentAnimation = m_spiderSprite->m_animationManager->m_currentAnimation;
        
        m_spiderBatchNode->removeMeAndCleanup();
        m_spiderBatchNode->release();
        
        m_spiderSprite = nullptr;
    }

    m_spiderSprite = GJSpiderSprite::create(frame);
    m_spiderSprite->m_delegate = this;
    m_spiderBatchNode = CCSpriteBatchNode::createWithTexture(m_spiderSprite->getTexture());
    m_spiderBatchNode->addChild(m_spiderSprite);
    m_spiderBatchNode->retain();

    if (spiderAlreadyExists)
    {
        if (m_isSpider)
            m_mainLayer->addChild(m_spiderBatchNode, 2);
        
        m_spiderSprite->m_color = color;
        m_spiderSprite->m_secondColor = secondColor;
        m_spiderSprite->updateColors();
        m_spiderSprite->updateGlowColor(m_playerColor2, false);
        m_spiderSprite->runAnimation(currentAnimation);
        
        if (isGlowSpriteVisible)
            m_spiderSprite->showGlow();
    }
}
