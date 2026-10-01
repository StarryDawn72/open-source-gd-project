void LevelInfoLayer::playStep2()
{
    FMODAudioEngine::sharedEngine()->loadMusic(
        m_level->getAudioFileName(),
        1.0f, // speed
        0.0f, // ??
        1.0f, // volume
        true, // shouldLoop
        0,    // musicID
        0,    // channelID
        false // dontReset
    );

    CCDelayTime* nextFrame = CCDelayTime::create(0.0f);
    CCCallFunc* callStep3  = CCCallFunc::create(this, callfunc_selector(LevelInfoLayer::playStep3));

    runAction(CCSequence::create(nextFrame, callStep3, NULL));
}