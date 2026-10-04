#define kTagGroundLine 2

void GJGroundLayer::createLine(int lineType)
{
    if (m_lineSprite) {
        m_lineSprite->removeFromParent();
        m_lineSprite = NULL;
    }

    lineType = MIN(MAX(lineType, 1), 3);
    float yPos;

    m_lineType = lineType;
    if (lineType == 1)
        yPos = 0.5f;
    else
        yPos = 0.2f;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    int style = (m_lineType == 1) ? 1 : 2;

    CCString* name = CCString::createWithFormat("floorLine_%02d_001.png", style);
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(name->getCString());

    m_lineSprite = sprite;
    addChild(sprite, 5);
    m_lineSprite->setPosition(ccp(winSize.width * 0.5f, yPos));
    m_lineSprite->setAnchorPoint(ccp(0.5f, 1.0f));
    m_lineSprite->setTag(kTagGroundLine);

    if (m_blendLine)
        m_lineSprite->setBlendFunc({GL_SRC_ALPHA, GL_ONE}); // Additive blending
        
    if (m_lineType == 3)
        m_lineSprite->setScaleY(2.0f);
    else
        m_lineSprite->setScaleX((winSize.width + 10.0f) / m_lineSprite->m_obRect.size.width);
}