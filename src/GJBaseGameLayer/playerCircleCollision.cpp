bool GJBaseGameLayer::playerCircleCollision(PlayerObject *player, GameObject *object)
{
    if (m_levelSettings->m_fixRadiusCollision)
        return playerIntersectsCircle(player, object);
    else
        return objectIntersectsCircle(player, object);
}