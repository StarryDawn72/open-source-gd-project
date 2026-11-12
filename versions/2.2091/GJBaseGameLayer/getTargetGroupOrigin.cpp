CCArray* GJBaseGameLayer::getTargetGroupOrigin(int index, int uniqueID)
{
    CCDictionary* group = (CCDictionary*)m_targetGroupsArray->objectAtIndex(index + 2);
    return (CCArray*)group->objectForKey(uniqueID);
}