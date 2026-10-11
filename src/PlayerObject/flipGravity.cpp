#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::flipGravity(bool flip, bool noEffects)
{
    if (m_isUpsideDown != flip) {

        placeStreakPoint();
        m_isUpsideDown = flip;

        if (m_gameLayer) {
			GJGameEvent event = flip ? GJGameEvent::GravityInverted : GJGameEvent::GravityRestored;
            gameEventTriggered((int)event, 0);
        }

        m_lastFlipTime = m_totalTime;
        m_collidedBottomMaxY = 0.0;
        m_collidedTopMinY = 0.0;
        m_hasHitGroundAfterGravityChange = false;

        if (m_wasOnSlope || m_isOnSlope)
            m_isGoingDownSlope = !m_isGoingDownSlope;
		
        resetCollisionLog(true);

        if (!m_isRespawning) {
            m_yVelocity *= 0.5;

            if (!noEffects) {
				ccColor3B effectColor = flip
					? ccc3(255, 200, 0)
					: ccc3(0, 150, 255);

                spawnPortalCircle(effectColor, 45.0f);
            }
        }
        updatePlayerScale();
        updatePlayerArt();

        if (!m_isBall
          && PL
          && !PL->m_freezeStartCamera
          && !m_isDart
          && !m_isRespawning)
        {
            m_shouldTryPlacingCheckpoint = 1;
            activateStreak();
        }

        m_lastGroundedPos = m_lastEffectObjectPos;
        m_canJump = false;

        if (m_isBall) {
            stopRotation(true, 6);
            runBallRotation2();
        }
        else if (m_isSwing) {
            updateSwingFire();
        }
    }
}