void GJBaseGameLayer::swapGround(int ground)
{
    m_gameState.m_ground = ground;
    if (!m_skipArtReload && GameManager::sharedState()->m_loadedGroundID != ground)
        GameManager::sharedState()->loadGroundAsync(ground);
}