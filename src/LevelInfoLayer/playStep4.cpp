#define GM GameManager::sharedState()

void LevelInfoLayer::playStep4()
{
    dwTickEnd = clock();
    dwDuration = dwTickEnd - dwTickStart;

    GM->m_loadingLevel = false;

    CCTransitionFade* fade = CCTransitionFade::create(0.5f, m_playScene);
    CCDirector::sharedDirector()->replaceScene(fade);

    m_playScene->release();
    m_playScene = NULL;
}