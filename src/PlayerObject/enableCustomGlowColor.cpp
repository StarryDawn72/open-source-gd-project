// @version 2.2081
void PlayerObject::enableCustomGlowColor(const cocos2d::ccColor3B& color)
{
    m_hasCustomGlowColor = true;
    m_glowColor = color;
}