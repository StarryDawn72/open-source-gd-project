void CCLightning::strike()
{
    runAction(CCSequence::create(
        CCShow::create(),
        CCFadeOut::create(m_duration),
        CCCallFunc::create(this, callfunc_selector(CCLightning::strikeFinished)),
        NULL
    ));
}