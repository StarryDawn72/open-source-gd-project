void GJBaseGameLayer::clearActivatedAudioTriggers()
{
    m_gameState.m_songChannelStates.clear();
    m_gameState.m_songTriggerStateVectors.clear();
    m_gameState.m_sfxTriggerStates.clear();
}