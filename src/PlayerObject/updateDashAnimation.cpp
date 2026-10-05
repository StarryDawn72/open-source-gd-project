void PlayerObject::updateDashAnimation()
{
    float frameDuration = (0.04f / m_playerSpeed) * (1.0f - fabsf(m_dashFireSprite->getRotation()) / 70.0 * 0.4f);
    float animProgress = m_totalTime / frameDuration;
    int frame = (int)floorf(animProgress) % 12 + 1;
    
    if (frame == m_dashFireFrame)
        return;

    m_dashFireFrame = frame;

    CCSprite* currentAnimFrame = (CCSprite*)m_dashFireSprite->getChildren()->objectAtIndex(0);

    CCString* dash = CCString::createWithFormat("playerDash2_%03d.png", frame);
    CCString* dashOutline = CCString::createWithFormat("playerDash2_outline_%03d.png", frame);

    if (dash->getCString())
    {
        m_dashFireSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(dash->getCString()));
        currentAnimFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(dashOutline->getCString()));

        CCSize spriteSize = m_dashFireSprite->getContentSize();
        currentAnimFrame->setPosition(ccp(spriteSize.width * 0.5f, spriteSize.height * 0.5f));
    }
}