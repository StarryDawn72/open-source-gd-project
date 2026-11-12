bool GJBaseGameLayer::canTouchObject(GameObject* object)
{
    int currentChannel = m_gameState.m_currentChannel;

    if (currentChannel != 0 && object->m_classType == GameObjectClassType::Effect)
    {
        EffectGameObject* obj = (EffectGameObject*)object;
        int channel = obj->m_channelValue;
        
        return channel == 0 || channel == currentChannel;
    }
    else
        return true;
}