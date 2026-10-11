GameObject* GJBaseGameLayer::getGroupParent(int groupId)
{
    return (GameObject*)m_parentGroupsDict->objectForKey(groupId);
}