void PlayerObject::fadeOutStreak2(float duration)
{
    if (!m_waveTrail->getActionByTag(8))
    {
        CCFadeOut* fadeOut = CCFadeOut::create(duration);
        CCCallFunc* stopCall = CCCallFunc::create(m_waveTrail, callfunc_selector(HardStreak::stopStroke));
        CCSequence* fadeSequence = CCSequence::create(fadeOut, stopCall, nullptr);

        fadeSequence->setTag(8);
        m_waveTrail->runAction(fadeSequence);
    }
}