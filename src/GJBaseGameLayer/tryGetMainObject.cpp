GameObject* GJBaseGameLayer::tryGetMainObject(int groupID)
{
    if (groupID <= 0)
        return nullptr;
    auto object = (GameObject*)m_parentGroupsDict->objectForKey(groupID);
    if (!object)
        return getSingleGroupObject(groupID);
    return object;
}