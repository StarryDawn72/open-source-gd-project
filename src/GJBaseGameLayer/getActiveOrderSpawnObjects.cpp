CCArray* GJBaseGameLayer::getActiveOrderSpawnObjects()
{
    auto res = (CCArray*)m_spawnObjects->objectForKey(m_gameState.m_currentChannel);
    if (!res)
        return CCArray::create();
    return res;
}