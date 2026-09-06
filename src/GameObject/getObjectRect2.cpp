const cocos2d::CCRect& GameObject::getObjectRect2(float width, float height)
{
    CCRect rect;

    if (m_isObjectRectDirty) {
        m_isObjectRectDirty = false;

        if (m_shouldUseOuterOb)
            rect = getOuterObjectRect();
        else
            rect = getObjectRect(width, height);

        m_objectRect = rect;
    }
    
    return m_objectRect;
}