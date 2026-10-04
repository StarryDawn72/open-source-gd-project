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