CCArray* GJBaseGameLayer::getTargetGroup(int index, int uniqueID)
{
    CCDictionary* group = (CCDictionary*)m_targetGroupsArray->objectAtIndex(index + 1);
    return (CCArray*)group->objectForKey(uniqueID);
}