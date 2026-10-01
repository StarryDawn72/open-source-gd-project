void LevelInfoLayer::onPlay(CCObject *sender)
{
    // These were most likely macros in the source code
    const char* kGVDisableSongAlert = "0083";
    const char* kGVShownCoinDisclaimer = "0063";
    const char* kGVDisableHighObjectAlert = "0082";
    int kMaxDailyID = 100000;
    int kTagAlertHighObjectCount = 10;

    if (m_isBusy || !m_enterTransitionFinished)
        return;

    if (shouldDownloadLevel()) {
        LevelInfoLayer::downloadLevel();
        return;
    }

    if (!GM->getGameVariable(kGVDisableSongAlert) &&
         m_level->m_songID != 0 &&
        !m_level->m_showedSongWarning &&
        !MusicDownloadManager::sharedState()->isSongDownloaded(m_level->m_songID))
    {
        showSongWarning();
        return;
    }

    if (m_level->m_coins > 0 &&
        m_level->m_coinsVerified.value() == 0 &&
        !GM->getGameVariable(kGVShownCoinDisclaimer))
    {
        GM->setGameVariable(kGVShownCoinDisclaimer, true);

        FLAlertLayer* coinAlert = FLAlertLayer::create(
            this,
            "Unverified Coins",

            "This level contains <cr>unverified</c> user coins (bronze).\n"
            "The coins will not count until they become <cg>verified</c> (silver).",

            "OK",
            NULL,
            300.0f
        );
        
        coinAlert->show();
        return;
    }

    if (!GM->getGameVariable(kGVDisableHighObjectAlert) &&
        m_level->m_objectCount.value() > 40000 &&
        !m_level->m_highObjectsEnabled)
    {
        const char* message;
        if (m_level->m_objectCount.value() <= 80000)
            message = "This level has a <co>high object</c> count and can be <cr>unstable</c> on some dev"
                        "ices. This may effect <cg>performance</c>, <cl>load time</c> etc.";
        else
            message = "This level has a <cr>VERY HIGH object</c> count and can be <cr>unstable</c> on som"
                        "e devices. This may effect <cg>performance</c>, <cl>load time</c> etc.";

        FLAlertLayer* highObjectAlert = FLAlertLayer::create(
            this,
            "High Objects",
            message,
            "Cancel",
            "Play",
            380.0f
        );

        highObjectAlert->setTag(kTagAlertHighObjectCount);
        highObjectAlert->show();
        return;
    }

    if (m_isBusy) return;

    setKeypadEnabled(false);
    m_isBusy = true;

    FMODAudioEngine::sharedEngine()->stopAllMusic(true);
    FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg", 1.0f, 0.0f, 0.3f);

    GM->m_loadingLevel = true;

    CCDelayTime* nextFrame = CCDelayTime::create(0.0f);
    CCCallFunc* callStep2 = CCCallFunc::create(this, callfunc_selector(LevelInfoLayer::playStep2));
    CCSequence* playAction = CCSequence::create(nextFrame, callStep2, NULL);
    runAction(playAction);

    ccColor3B menuBGColor = ccc3(0, 46, 115);
    ccColor3B menuBGColorLighter = ccc3(0, 87, 218);
    ccColor3B progressRingColor = ccc3(100, 255, 0);

    if (m_level->m_dailyID.value() > kMaxDailyID) {
        menuBGColor = ccc3(23, 23, 23);
        menuBGColorLighter = ccc3(43, 43, 43);
        progressRingColor = ccc3(255, 50, 0);
    }
    else if (m_level->m_gauntletLevel) {
        menuBGColor = ccc3(23, 23, 23);
        menuBGColorLighter = ccc3(43, 43, 43);
    }

    CCSprite* progressShadow = CCSprite::createWithSpriteFrameName("d_circle_01_001.png");
    progressShadow->setColor(menuBGColor);
    progressShadow->setScale(1.88f);
    progressShadow->setPosition(ccp(
        m_playSprite->getContentSize().width  * 0.5f,
        m_playSprite->getContentSize().height * 0.5f
    ));
    m_playSprite->addChild(progressShadow, -5);

    CCSprite* progressOverlay = CCSprite::createWithSpriteFrameName("d_circle_01_001.png");
    progressOverlay->setColor(menuBGColor);
    progressOverlay->setScale(1.63f);
    progressOverlay->setPosition(ccp(
        m_playSprite->getContentSize().width  * 0.5f,
        m_playSprite->getContentSize().height * 0.5f
    ));
    m_playSprite->addChild(progressOverlay, -2);

    CCSprite* progressGroove = CCSprite::createWithSpriteFrameName("d_circle_01_001.png");
    progressGroove->setColor(menuBGColorLighter);
    progressGroove->setScale(1.75f);
    progressGroove->setPosition(ccp(
        m_playSprite->getContentSize().width  * 0.5f,
        m_playSprite->getContentSize().height * 0.5f
    ));
    m_playSprite->addChild(progressGroove, -4);
    
    m_playSprite->setColor(ccc3(125, 125, 125));

    CCSprite* progressRing = CCSprite::createWithSpriteFrameName("d_circle_01_001.png");
    progressRing->setColor(progressRingColor);

    CCProgressTimer* timer = CCProgressTimer::create(progressRing);
    m_progressTimer = timer;
    timer->setPosition(ccp(
        m_playSprite->getContentSize().width  * 0.5f,
        m_playSprite->getContentSize().height * 0.5f                                
    ));
    m_progressTimer->setScale(1.75f);
    m_progressTimer->setPercentage(0.0f);

    m_playSprite->addChild(m_progressTimer, -3);
    m_playBtnMenu->setTouchEnabled(false);
    m_songWidget->m_buttonMenu->setTouchEnabled(false);
}