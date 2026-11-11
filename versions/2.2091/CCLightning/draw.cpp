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