void GJBaseGameLayer::processAreaVisualActions(float dt)
{
    processAreaEffects(&m_gameState.m_fadeEffectInstances, GJAreaActionType::Fade, dt, true);
    processAreaEffects(&m_gameState.m_tintEffectInstances, GJAreaActionType::Tint, dt, true);
}