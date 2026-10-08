#define GM GameManager::sharedState()

#define kMaxPlayerStreak 7

// UNFINISHED
void PlayerObject::setupStreak() {
    m_playerStreak = MAX(1, MIN(GM->m_playerStreak.value(), kMaxPlayerStreak));

    m_hasGlow = GM->m_playerGlow;

    m_streakStrokeWidth = 10.0f;
    float fade = 0.3f;

    switch (m_playerStreak) {
    case 2:
    case 7:
        m_streakStrokeWidth = 14.0f;
        m_disableStreakTint = true;
        break;
    case 3:
        m_streakStrokeWidth = 8.5f;
        break;
    case 4:
        fade = 0.4f;
        break;
    case 5:
        m_streakStrokeWidth = 5.0f;
        m_alwaysShowStreak = true;
        fade = 0.4f;
        break;
    case 6:
        m_streakStrokeWidth = 3.0f;
        m_alwaysShowStreak = true;
        fade = 1.0f;
        break;
    }

    const char* streakName = CCString::createWithFormat("streak_%02d_001.png", m_playerStreak)->getCString();
    m_regularTrail = CCMotionStreak::create(fade, 5.0f, m_streakStrokeWidth, ccWHITE, streakName);

    if (m_playerStreak == 6)
        m_regularTrail->enableRepeatMode(0.1f);

    m_regularTrail->m_fMaxSeg = 50.0f;
    m_parentLayer->addChild(m_regularTrail, -2);

    ShipStreak shipStreak = (ShipStreak)GM->m_playerShipFire.value();
    if (shipStreak > ShipStreak::ShipFire6)
        shipStreak = ShipStreak::ShipFire1;
    m_shipStreakType = shipStreak;

    if (m_shipStreakType > ShipStreak::ShipFire1) {
        // Another stupid private function
        // I can't do this... I'm skipping
    }
}