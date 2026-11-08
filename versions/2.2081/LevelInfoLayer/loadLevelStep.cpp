void LevelInfoLayer::loadLevelStep()
{
    PlayLayer* playLayer = (PlayLayer*)m_playScene->getChildren()->objectAtIndex(0);
    playLayer->processCreateObjectsFromSetup();

    m_progressTimer->setPercentage(playLayer->m_loadingProgress * 100.0f);

    auto nextStepSelector = (playLayer->m_loadingProgress >= 1.0f)
                    ? callfunc_selector(LevelInfoLayer::playStep4)
                    : callfunc_selector(LevelInfoLayer::loadLevelStep);

    CCDelayTime* nextFrame = CCDelayTime::create(0.0f);
    CCCallFunc* nextStep   = CCCallFunc::create(this, nextStepSelector);

    CCNode::runAction(CCSequence::create(nextFrame, nextStep, NULL));
}