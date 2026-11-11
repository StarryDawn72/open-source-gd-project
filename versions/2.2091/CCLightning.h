#pragma once

#include "cocos2d.h"

namespace cocos2d 
{ 

class CCLightning : public CCNode, public CCRGBAProtocol {
public:

    ~CCLightning();

    static CCLightning* lightningWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration);
    static CCLightning* lightningWithStrikePoint(CCPoint strikePoint);

    void strikeFinished();
    void draw();
    void strike();
    bool initWithStrikePoint(CCPoint strikePoint1, CCPoint strikePoint2, float duration);
    bool initWithStrikePoint(CCPoint strikePoint);
    void strikeRandom();
    void strikeWithSeed(uint64_t seed);

    // CCRGBAProtocol
    GLubyte getOpacity();
    GLubyte getDisplayedOpacity();
    void setOpacity(GLubyte opacity);
    const ccColor3B& getColor();
    void setColor(const ccColor3B& color);
    bool isOpacityModifyRGB();
    void setOpacityModifyRGB(bool bValue);
    void updateDisplayedOpacity(GLubyte opacity);
    bool isCascadeOpacityEnabled();
    void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    const ccColor3B& getDisplayedColor();
    void updateDisplayedColor(const ccColor3B& color);
    bool isCascadeColorEnabled();
    void setCascadeColorEnabled(bool cascadeColorEnabled);

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

}