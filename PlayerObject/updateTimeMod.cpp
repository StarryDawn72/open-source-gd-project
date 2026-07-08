#define GM GameManager::sharedState() // as seen in RobTop's streams

/*
	====== PLAYEROBJECT::UPDATETIMEMOD ======

	This function is the core speed engine of Geometry Dash. it takes
	the "speed" parameter to decide which of the five particle effects to play,
	then updates the jump velocity, gravity, and time mod (m_speedMultplier).
	
*/
void PlayerObject::updateTimeMod(float speed, bool noEffects)
{

	bool hasPlayLayer = m_playEffects;
    if (!m_maybeReducedEffects && hasPlayLayer && !noEffects && m_playerSpeed != speed) {
        GM->playSpeedParticle(speed);
    }

    m_playerSpeed = speed;
    if (speed == 0.9f) {
        m_yStart = 11.180032f;
        m_gravity = 0.958199f;
		m_speedMultiplier = 5.770002f;
    }
	else if (speed == 0.7f) {
		m_yStart = 10.620032;
		m_gravity = 0.940199;
		m_speedMultiplier = 5.980002;
	}
	else if (speed == 1.1f) {
		m_yStart = 11.420032;
		m_gravity = 0.957199;
		m_speedMultiplier = 5.870002;
	}
	else if (speed == 1.3f || speed == 1.6f) {
		m_yStart = 11.230032;
		m_gravity = 0.961199;
		m_speedMultiplier = 6.000002;
	}

    updateRobotAnimationSpeed();

    if (m_isBall) {
        runRotateAction(false, 0);
    }

    if (m_shipStreak) m_shipStreak->updateStreakSettings(m_shipStreakType, this);
}