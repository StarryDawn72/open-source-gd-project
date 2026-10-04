#include "GJGroundLayer.h"

#define kTagGroundShadowLeft 0
#define kTagGroundShadowRight 1
#define kTagGroundLine 2
#define kTagGroundFade 3

void GJGroundLayer::showGround()
{
    m_showGround = true;
}

void GJGroundLayer::fadeOutGround(float duration)
{
    m_showGround = false;
}

void GJGroundLayer::fadeInFinished()
{
    m_showGround = true;
}

void GJGroundLayer::draw()
{
    
}

void GJGroundLayer::fadeInGround(float duration)
{
    stopActionByTag(kTagGroundFade);

    CCDelayTime* delay = CCDelayTime::create(duration);
    CCCallFunc* finishCall = CCCallFunc::create(this, callfunc_selector(GJGroundLayer::fadeInFinished));
    CCSequence* action = CCSequence::create(finishCall, NULL); // Not a bug in the reconstruction

    action->setTag(kTagGroundFade);
    runAction(action);
}

void GJGroundLayer::toggleVisible01(bool visible)
{
    if (m_showGround1 != visible) {
        m_showGround1 = visible;

        if (visible)
            visible = m_showGround2;

        setVisible(visible);
    }
}

void GJGroundLayer::toggleVisible02(bool visible)
{
    if (m_showGround2 != visible)
    {
        m_showGround2 = visible;

        if (!m_showGround1)
            visible = false;

        setVisible(visible);
    }
}

void GJGroundLayer::loadGroundSprites(int count, bool floor)
{
    CCSprite* ground = floor ? m_ground1Sprite : m_ground2Sprite;

    if (!ground) return;

    CCArray* groundSprites = CCArray::create();

    if (ground->getChildren()) {
        groundSprites->addObjectsFromArray(ground->getChildren());
    }

    if (groundSprites->count() == count) return;

    if (groundSprites->count() >= count) {
        for (int i = groundSprites->count() - count; i > 0 && groundSprites->count(); i--)
        {
            ground->removeChild((CCNode*)groundSprites->lastObject(), true);
            groundSprites->removeLastObject(true);
        }
    }
    else {
        for (int i = groundSprites->count(); i < count; i++)
        {
            CCSprite* tile = CCSprite::createWithTexture(ground->getTexture());
            ground->addChild(tile);
            
            float y = floor ? -m_ground1Offset : 0.0f;

            tile->setPosition(ccp(i * tile->m_obRect.size.width, y));
            tile->setAnchorPoint(ccp(0.0f, 1.0f));
            tile->setColor(ccc3(166, 166, 166));
        }
    }
}

void GJGroundLayer::updateGroundPos(CCPoint pos)
{
    m_ground1Sprite->setPosition(pos);
    if (m_ground2Sprite) m_ground2Sprite->setPosition(pos);
}

void GJGroundLayer::updateGround01Color(ccColor3B color)
{
    CCArray* children = this->m_ground1Sprite->getChildren();

    if (children) {
        for (int i = 0; i < children->count(); i++) {
            CCSprite* sprite = (CCSprite*)children->objectAtIndex(i);
            sprite->setColor(color);
        }
    }
}

void GJGroundLayer::updateGround02Color(ccColor3B color)
{
    if (m_ground2Sprite) {
        CCArray* children = m_ground2Sprite->getChildren();

        if (children) {
            for (int i = 0; i < children->count(); i++) {
                CCSprite* sprite = (CCSprite*)children->objectAtIndex(i);
                sprite->setColor(color);
            }
        }
    }
}

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

GJGroundLayer* GJGroundLayer::create(int groundID, int lineType)
{
    GJGroundLayer* ret = new GJGroundLayer();

    if (ret->init(groundID, lineType)) {
        ret->autorelease();
        return ret;
    }

    ret = NULL;
    return ret;
}

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

void GJGroundLayer::updateLineBlend(bool blend)
{
    if (m_blendLine != blend) {
        m_blendLine = blend;

        ccBlendFunc blendFunc = blend
            ? ccBlendFunc(GL_SRC_ALPHA, GL_ONE)
            : ccBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        m_lineSprite->setBlendFunc(blendFunc);
    }
}

void GJGroundLayer::hideShadows()
{
    CCNode* lShadow = getChildByTag(kTagGroundShadowLeft);
    CCNode* rShadow = getChildByTag(kTagGroundShadowRight);

    if (lShadow) lShadow->setVisible(false);
    if (rShadow) rShadow->setVisible(false);
}

void GJGroundLayer::updateShadows()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCNode* rShadow = getChildByTag(kTagGroundShadowRight);

    if (rShadow)
        rShadow->setPosition(ccp(winSize.width / getScaleX() + 1.0f, 0.0f));
}

float GJGroundLayer::scaleGround(float scale)
{
    setScaleX(scale);
    setScaleY(getScaleY() >= 0.0f ? scale : -scale);

    float preWidth = m_groundWidth;
    updateGroundWidth(true);
    float postWidth = m_groundWidth;

    updateShadows();

    return postWidth - preWidth;
}

void GJGroundLayer::updateShadowXPos(float leftX, float rightX)
{

    float scaleX = getScaleX(); // Presumably a leftover from the source code,
                                // result is unused

    CCNode* lShadow = getChildByTag(kTagGroundShadowLeft);
    if (lShadow)
        lShadow->setPosition(ccp(leftX - 1.0f, 0.0f));

    CCNode* rShadow = getChildByTag(kTagGroundShadowRight);
    if (rShadow)
        rShadow->setPosition(ccp(rightX + 1.0f, 0.0f));
}

void GJGroundLayer::deactivateGround()
{
    stopAllActions();
    m_showGround = false;
}

void GJGroundLayer::positionGround(float y)
{
    setPosition(ccp(0.0f, y));
}

float GJGroundLayer::getGroundY()
{
    return 0.0f;
}