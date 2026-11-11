#include "CCLightning.h"

#define kMaxPoints 200

using namespace cocos2d;

CCLightning::~CCLightning()
{
    CC_SAFE_DELETE_ARRAY(m_lightningPoints)
}

GLubyte CCLightning::getOpacity()
{
    return m_opacity;
}

GLubyte CCLightning::getDisplayedOpacity()
{
    return getOpacity();
}

void CCLightning::setOpacity(GLubyte opacity)
{
    m_opacity = opacity;
}

const ccColor3B& CCLightning::getColor()
{
    return m_color;
}

void CCLightning::setColor(const ccColor3B& color)
{
    m_color = color;
}

bool CCLightning::isOpacityModifyRGB()
{
    return m_opacityModifyEnabled;
}

void CCLightning::setOpacityModifyRGB(bool bValue)
{
    m_opacityModifyEnabled = bValue;
}

void CCLightning::updateDisplayedOpacity(GLubyte opacity)
{
    m_displayedOpacity = opacity;
}

bool CCLightning::isCascadeOpacityEnabled()
{
    return m_cascadeOpacityEnabled;
}

void CCLightning::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    m_cascadeOpacityEnabled = cascadeOpacityEnabled;
}

const ccColor3B& CCLightning::getDisplayedColor()
{
    return m_displayedColor;
}

void CCLightning::updateDisplayedColor(const ccColor3B& color)
{
    m_displayedColor = color;
}

bool CCLightning::isCascadeColorEnabled()
{
    return m_cascadeColorEnabled;
}

void CCLightning::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    m_cascadeColorEnabled = cascadeColorEnabled;
}

void CCLightning::strikeFinished()
{
    if (m_removeAfterFinished) removeMeAndCleanup();
}

void CCLightning::draw()
{
    m_numPoints = 0;

    ccDrawColor4B(m_color.r, m_color.g, m_color.b, (m_opacity * m_opacityModify));
    glLineWidth(m_lineWidth);
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE);

    CCPoint midPoint = drawLightning(ccp(0.0f, 0.0f), m_strikePoint, m_displacement, m_minDisplacement, m_seed, m_lightningPoints, &m_numPoints);

    if (m_split) {
        drawLightning(midPoint, m_strikePoint2, m_displacement / 2, m_minDisplacement, m_seed, m_lightningPoints, &m_numPoints);
    }

    ccDrawLines(m_lightningPoints, m_numPoints);
}

void CCLightning::strike()
{
    runAction(CCSequence::create(
        CCShow::create(),
        CCFadeOut::create(m_duration),
        CCCallFunc::create(this, callfunc_selector(CCLightning::strikeFinished)),
        NULL
    ));
}

bool CCLightning::initWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration)
{
    m_strikePoint = strikePoint1;
    m_strikePoint2 = strikePoint2;
    m_color = ccc3(255, 255, 255);
    m_opacity = 255;
    m_seed = rand();
    m_duration = duration;
    m_split = false;

    // constants
    m_displacement = 160;
    m_numPoints = 0;
    m_minDisplacement = 8;

    m_lightningPoints = new CCPoint[kMaxPoints];
    memset(m_lightningPoints, 0, sizeof(CCPoint) * kMaxPoints);
    m_unkBool = false;

    strike();
    return true;
}

bool CCLightning::initWithStrikePoint(CCPoint strikePoint)
{
    return initWithStrikePoint(strikePoint, CCPointZero, 0.5f);
}

CCLightning* CCLightning::lightningWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration)
{
    CCLightning* ret = new CCLightning();

    if (ret->initWithStrikePoint(strikePoint1, strikePoint2, duration)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return NULL;
    }
}

CCLightning* CCLightning::lightningWithStrikePoint(CCPoint strikePoint)
{
    CCLightning* ret = new CCLightning();

    if (ret->initWithStrikePoint(strikePoint)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return NULL;
    }
}

void CCLightning::strikeRandom()
{
    m_seed = rand();
    strike();
}

void CCLightning::strikeWithSeed(uint64_t seed)
{
    m_seed = seed;
    strike();
}