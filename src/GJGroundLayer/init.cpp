#define GM GameManager::sharedState()
#define kTagGroundShadowLeft 0
#define kTagGroundShadowRight 1

bool GJGroundLayer::init(int groundID, int lineType)
{
    if (!CCLayer::init()) {
        return false;
    }

    setContentSize(CCSizeZero);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    const char* groundTextureName = GM->getGTexture(groundID);
    
    m_blendLine = true;
    createLine(lineType);

    CCSprite* leftShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    leftShadow->setAnchorPoint(ccp(0.0f, 1.0f));
    float screenLeft = CCDirector::sharedDirector()->getScreenLeft();
    leftShadow->setPosition(ccp(screenLeft - 1.0f, 0.0f));
    addChild(leftShadow, 6);
    leftShadow->setTag(kTagGroundShadowLeft);

    CCSprite* rightShadow = CCSprite::createWithSpriteFrameName("groundSquareShadow_001.png");
    rightShadow->setAnchorPoint(ccp(1.0f, 1.0f));
    float screenRight = CCDirector::sharedDirector()->getScreenRight();
    rightShadow->setPosition(ccp(screenRight + 1.0f, 0.0f));
    addChild(rightShadow, 6);

    rightShadow->setFlipX(true);
    rightShadow->setTag(kTagGroundShadowRight);

    leftShadow->setOpacity(100);
    rightShadow->setOpacity(100);

    leftShadow->setScaleX(0.7f);
    rightShadow->setScaleX(0.7f);
                        
    // Multiplicative blending
    leftShadow->setBlendFunc({GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA});
    rightShadow->setBlendFunc({GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA});

    m_showGround = false;
    ccColor3B defaultGroundColor = ccc3(0, 102, 255);

    CCSpriteBatchNode* primaryNode = CCSpriteBatchNode::create(groundTextureName);
    addChild(primaryNode, 2);

    CCSize textureSize = primaryNode->getTexture()->getContentSize();
    m_textureWidth = textureSize.width;

    int tileCount = ceilf(winSize.width / textureSize.width) + 1.0;
    m_ground1Offset = 128.0f - textureSize.height;

    CCSprite* primarySprite = CCSprite::createWithTexture(primaryNode->getTexture(), CCRectZero);
    m_ground1Sprite = primarySprite;

    primarySprite->m_bDontDraw = true;
    primarySprite->setPosition(ccp(0.0f, 0.0f));
    m_ground1Sprite->setColor(defaultGroundColor);

    primaryNode->addChild(m_ground1Sprite);
    primaryNode->setBlendFunc({GL_ONE, GL_ZERO});

    loadGroundSprites(tileCount, true);
    updateGround01Color(defaultGroundColor);

    if (groundID >= 8) {
        CCString* secondaryTextureName = CCString::createWithFormat("groundSquare_%02d_2_001.png", groundID);
        CCSpriteBatchNode* secondaryNode = CCSpriteBatchNode::create(secondaryTextureName->getCString());

        addChild(secondaryNode, 3);
        CCSprite* secondarySprite = CCSprite::createWithTexture(secondaryNode->getTexture(), CCRectZero);
        m_ground2Sprite = secondarySprite;

        secondarySprite->m_bDontDraw = true;
        secondarySprite->setPosition(ccp(0.0f, 0.0f));
        m_ground2Sprite->setColor(defaultGroundColor);

        secondaryNode->addChild(m_ground2Sprite);

        loadGroundSprites(tileCount, false);
        updateGround01Color(defaultGroundColor);
    }

    return true;
}