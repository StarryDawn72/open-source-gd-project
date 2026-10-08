#define GM GameManager::sharedState()
#define kMaxPlayerStreak 7

void PlayerObject::setupStreak()
{
    m_playerStreak = MIN(MAX(GM->m_playerStreak.value(), 1), kMaxPlayerStreak);
    m_hasGlow = GM->m_playerGlow;

    CCString* streakName = CCString::createWithFormat("streak_%02d_001.png", m_playerStreak);

    m_streakStrokeWidth = 10.0f;

    float fade = 0.3f;

    switch (m_playerStreak) {
        case 2:
        case 7:
            m_streakStrokeWidth = 14.0f;
            m_disableStreakTint = true;
            fade = 0.3f;
            break;
        case 3:
            m_streakStrokeWidth = 8.5f;
            fade = 0.3f;
            break;
        case 4:
            fade = 0.4f;
            break;
        case 5:
            m_streakStrokeWidth = 5.0f;
            m_alwaysShowStreak = true;
            fade = 0.6f;
            break;
        case 6:
            m_alwaysShowStreak = true;
            m_streakStrokeWidth = 3.0f;
            fade = 1.0f;
            break;
    }

    m_regularTrail = CCMotionStreak::create(fade, 5.0f, m_streakStrokeWidth, ccWHITE, streakName->getCString());
    
    if ((ShipStreak)m_playerStreak == ShipStreak::ShipFire6)
        m_regularTrail->enableRepeatMode(0.1f);

    m_regularTrail->m_fMaxSeg = 50.0f;
    m_parentLayer->addChild(m_regularTrail, -2);

    ShipStreak type = (ShipStreak)GM->m_playerShipFire.value();

    if (type > ShipStreak::ShipFire6)
        type = ShipStreak::ShipFire1;

    m_shipStreakType = (ShipStreak)type;

    if (m_shipStreakType > ShipStreak::ShipFire1) {
        float fadeTime = 0.0f;
        float strokeWidth = 0.0f;

        getSettingsForStreak((int)m_shipStreakType, 1.6f, 1.0f, fadeTime, strokeWidth);

        std::string frame = getFrameForStreak(m_shipStreakType, 0.0f);

        CCTexture2D* streakTexture = CCTextureCache::sharedTextureCache()->addImage(frame.c_str(), false);
        m_shipStreak = CCMotionStreak::create(fadeTime, 1.0f, strokeWidth, ccWHITE, streakTexture);
        m_parentLayer->addChild(m_shipStreak, -3);

        m_shipStreak->m_bDontOpacityFade = true;
        m_shipStreak->m_fMaxSeg = 50.0f;

        ccBlendFunc blend = ccBlendFunc(GL_SRC_ALPHA, GL_ONE);
        m_shipStreak->setBlendFunc(blend);
    }

    ccBlendFunc blend = ccBlendFunc(GL_SRC_ALPHA, GL_ONE);

    m_regularTrail->setBlendFunc(blend);
    
    HardStreak* waveTrail = HardStreak::create();
    m_waveTrail = waveTrail;

    m_parentLayer->addChild(waveTrail, -3);

    if (GM->m_playerColor.value() != 15 || m_switchWaveTrailColor)
        m_waveTrail->setBlendFunc(blend);
    else
        m_waveTrail->m_isSolid = true;

    deactivateStreak(true);
}
