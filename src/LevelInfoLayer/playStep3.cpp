#define GM GameManager::sharedState()

void LevelInfoLayer::playStep3()
{
    GM->m_sceneEnum = 3; // what

    CCScene* scene = PlayLayer::scene(m_level, false, true);
    m_playScene = scene;
    scene->retain();

    CCDelayTime* nextFrame    = CCDelayTime::create(0.0f);
    CCCallFunc* loadLevelCall = CCCallFunc::create(this, callfunc_selector(LevelInfoLayer::loadLevelStep));

    runAction(CCSequence::create(nextFrame, loadLevelCall, NULL));

    // idk what this is
    dwTickStart = clock();
}