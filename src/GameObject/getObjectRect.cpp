CCRect GameObject::getObjectRect(float width, float height)
{
    // Rename incorrect bindings
    bool m_hasSwappedDimensions = m_isRotationAligned;

    if (m_isMirroredByScale) {
        m_scaleX = fabs(m_scaleX);
        m_scaleY = fabs(m_scaleY);
    }

    CCSize size = CCSizeMake(m_width * m_scaleX, m_height * m_scaleY);

    size.width *= width;
    size.height *= height;

    CCPoint intrinsicOffset = getBoxOffset();

    if (m_hasSwappedDimensions) {
        float h = size.height;
        size.height = size.width;
        size.width = h;
    }

    CCPoint pos = getRealPosition() + intrinsicOffset;

    return CCRectMake(
        pos.x - (size.width / 2),
        pos.y - (size.height / 2),
        size.width,
        size.height
    );
}

const CCRect& GameObject::getObjectRect()
{
    return getObjectRect2(m_spriteWidthScale, m_spriteHeightScale);
}