void GJBaseGameLayer::controlDynamicMoveCommand(EffectGameObject* object, int controlID, GJActionCommand command)
{
    controlDynamicCommand(object, controlID, m_gameState.m_dynamicMoveActions, command);
}