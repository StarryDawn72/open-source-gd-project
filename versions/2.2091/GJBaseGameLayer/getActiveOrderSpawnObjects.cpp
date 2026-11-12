CCArray* GJBaseGameLayer::getActiveOrderSpawnObjects()
{

    CCArray* objects = (CCArray*)m_spawnObjects->objectForKey(m_gameState.m_currentChannel);

    if (!objects)
        return CCArray::create();
    else
        return objects;
}