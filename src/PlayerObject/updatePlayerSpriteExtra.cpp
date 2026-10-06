void PlayerObject::updatePlayerSpriteExtra(gd::string frameName)
{
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
    if (frame)
    {
        m_iconSpriteWhitener->setDisplayFrame(frame);
        m_iconSpriteWhitener->setVisible(true);
        m_iconSpriteWhitener->setPosition(m_iconSprite->getContentSize() * 0.5f);
    } else
        m_iconSpriteWhitener->setVisible(false);
}