void GJBaseGameLayer::pauseAudio()
{
    FMODAudioEngine::sharedEngine()->pauseAllAudio();
    FMODAudioEngine::sharedEngine()->pauseAllMusic(true);
    FMODAudioEngine::sharedEngine()->m_system->update();
}