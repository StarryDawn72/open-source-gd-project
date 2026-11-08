void GJGroundLayer::updateGroundWidth(bool scaled)
{
    if (!getParent())
        return;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    float scale = scaled ? getScaleX() : getParent()->getScale();

    float groundWidth = (winSize.width / scale) + 10.0f;
    m_groundWidth = groundWidth;

    int tileCount = (ceilf(groundWidth / m_textureWidth) + 1.0f);

    if (m_cameraRotated)
        tileCount++;

    loadGroundSprites(tileCount, true);  // Floor
    loadGroundSprites(tileCount, false); // Ceiling

    if (m_lineType > 1) {
        m_lineSprite->setScaleX(((winSize.width + 10.0f) / scale) / m_lineSprite->m_obRect.size.width);
    }
    else if (scaled) {
        m_lineSprite->setScaleX(1.0f / scale);
    }

    m_lineSprite->setPosition(ccp(
        (m_groundWidth * 0.5f) - 5.0f,
        m_lineSprite->getPosition().y)
    );
}