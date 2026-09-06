CCRect* getObjectRectPointer()
{
    if (m_isObjectRectDirty)
        getObjectRect();
    return &m_objectRect;
}