void GJBaseGameLayer::controlDynamicRotateCommand(EffectGameObject* object, int controlID, GJActionCommand command)
{
    controlDynamicCommand(object, controlID, m_gameState.m_dynamicRotateActions, command);
}