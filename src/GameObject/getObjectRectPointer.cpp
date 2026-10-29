// @version 2.2081
CCRect* getObjectRectPointer()
{
    if (m_isObjectRectDirty)
        getObjectRect();
    return &m_objectRect;
}