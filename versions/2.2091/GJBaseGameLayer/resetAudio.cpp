void GJBaseGameLayer::resetAudio()
{
    FMODAudioEngine::sharedEngine()->clearAllAudio();
    FMODAudioEngine::sharedEngine()->m_system->update();
}