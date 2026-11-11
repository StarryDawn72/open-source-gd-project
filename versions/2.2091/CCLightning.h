#pragma once

#include "cocos2d.h"

NS_CC_BEGIN

class CCLightning : public CCNode, public CCRGBAProtocol {
public:

    GLubyte CCLightning::getOpacity();
    GLubyte CCLightning::getDisplayedOpacity();
    void CCLightning::setOpacity(GLubyte opacity);

    const ccColor3B& CCLightning::getColor();

    void CCLightning::setColor(const ccColor3B& color);
    bool CCLightning::isOpacityModifyRGB();
    void CCLightning::setOpacityModifyRGB(bool bValue);
    void CCLightning::updateDisplayedOpacity(GLubyte opacity);
    bool CCLightning::isCascadeOpacityEnabled();
    void CCLightning::setCascadeOpacityEnabled(bool cascadeOpacityEnabled);

    const ccColor3B& CCLightning::getDisplayedColor();

    void CCLightning::updateDisplayedColor(const ccColor3B& color);
    bool CCLightning::isCascadeColorEnabled();
    void CCLightning::setCascadeColorEnabled(bool cascadeColorEnabled);
    void CCLightning::strikeFinished();
    void CCLightning::draw();
    void CCLightning::strike();

    bool CCLightning::initWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration);
    bool CCLightning::initWithStrikePoint(CCPoint strikePoint);

    CCLightning* CCLightning::lightningWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration);
    CCLightning* CCLightning::lightningWithStrikePoint(CCPoint strikePoint);

    void CCLightning::strikeRandom();
    void CCLightning::strikeWithSeed(uint64_t seed);

private:
    CCPoint m_strikePoint = CCPointZero;
    CCPoint m_strikePoint2 = CCPointZero;
    bool m_split = false;

    int m_displacement = 0;
    int m_minDisplacement = 0;
    unsigned long long m_seed = 0;
    bool m_removeAfterFinished = false;
    bool m_unkBool; // unused

    float m_lineWidth = 2;
    CCPoint* m_lightningPoints = NULL;
    float m_duration = 0.5f;
    unsigned int m_numPoints = 0;
    
    float m_opacityModify = 1.0f;

    GLubyte m_displayedOpacity = 0;
    GLubyte m_opacity = 0;
    ccColor3B m_displayedColor;
    ccColor3B m_color;

    bool m_cascadeColorEnabled = false;
    bool m_cascadeOpacityEnabled = false;
    bool m_opacityModifyEnabled = false;
};

NS_CC_END