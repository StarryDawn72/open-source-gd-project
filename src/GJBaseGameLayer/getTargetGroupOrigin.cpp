CCArray* GJBaseGameLayer::getTargetGroupOrigin(int index, int uniqueID)
{
    auto dict = (CCDictionary*)m_targetGroupsArray->objectAtIndex(index + 2);
    return (CCArray*)dict->objectForKey(uniqueID);
}