GameObject* GJBaseGameLayer::getSingleGroupObject(int groupID)
{
    if (groupID <= 0)
        return nullptr;

    CCArray* group = getGroup(groupID);
    if (group && group->count() == 1)
        return (GameObject*)group->objectAtIndex(0);
    return nullptr;
}