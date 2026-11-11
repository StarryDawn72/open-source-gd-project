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

    m_lightningPoints = new CCPoint[200];
    memset(m_lightningPoints, 0, sizeof(CCPoint) * 200);
    m_unkBool = false;

    strike();

    return true;
}

bool CCLightning::initWithStrikePoint(CCPoint strikePoint)
{
    return initWithStrikePoint(strikePoint, CCPointZero, 0.5f);
}