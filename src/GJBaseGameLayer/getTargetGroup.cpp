CCArray* GJBaseGameLayer::getTargetGroup(int index, int uniqueID)
{
    auto dict = (CCDictionary*)m_targetGroupsArray->objectAtIndex(index + 1);
    return (CCArray*)dict->objectForKey(uniqueID);
}