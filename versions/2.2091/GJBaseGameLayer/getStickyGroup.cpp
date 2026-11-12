CCArray* GJBaseGameLayer::getStickyGroup(int group)
{
    return (CCArray*)m_linkedGroupDict->objectForKey(group);
}