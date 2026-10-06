void PlayerObject::updateShipSpriteExtra(gd::string frameName) {
    CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
    if (frame)
    {
        m_vehicleSpriteWhitener->setDisplayFrame(frame);
        m_vehicleSpriteWhitener->setVisible(true);
        m_vehicleSpriteWhitener->setPosition(m_iconSprite->getContentSize() * 0.5f);
    } else
        m_vehicleSpriteWhitener->setVisible(false);
}