void GJBaseGameLayer::resumeAudio()
{
    FMODAudioEngine::sharedEngine()->resumeAudio();
    FMODAudioEngine::sharedEngine()->resumeAllAudio();
    AppDelegate::get()->resumeSound();
    FMODAudioEngine::sharedEngine()->m_system->update();
}