/*
    Runs on activation of a toggle orb (custom ring).
*/
void GJBaseGameLayer::activateCustomRing(RingObject* object)
{
    std::vector<int> remapKeys{};

    if (object->m_isSpawnOnly)
        spawnGroup(
            object->m_targetGroupID,
            false,
            0.0,
            remapKeys,
            object->m_uniqueID,
            object->m_controlID
        );
    else
        toggleGroupTriggered(
            object->m_targetGroupID,
            object->m_activateGroup,
            remapKeys,
            object->m_uniqueID,
            object->m_controlID
        );
}