#define GM GameManager::sharedState()
/*
	
	The central vertical physics updater that handles
	every game mode. Called at the beginning of the physics
	update branch in PlayerObject::update.
	
*/
void PlayerObject::updateJump(float dt)
{
	// rename incorrect geode bindings
	bool& m_isJumpUnused = m_stateRingJump;
	bool& m_isJumping = m_maybeIsBoosted;
	bool& m_isVelocityUncapped = m_isAccelerating;
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	float& m_playerScale = m_vehicleSize;
	bool& m_slopeForceLeft = m_platformerMovingLeft;
	bool& m_slopeForceRight = m_platformerMovingRight;
	int& m_slopeSlideTimer = m_maybeSlidingTime;
	bool& m_isSlopeUphillRelative = m_slopeSlidingMaybeRotated;
	bool& m_holdingJump = m_jumpBuffered;
	bool& m_wasHoldingJump = m_wasJumpBuffered;
	bool& m_isGroundTouchSideValid = m_isOnGround3;
	double& m_slopeForceEndTime = m_maybeSlidingStartTime;
	geode::SeedValueRSV& m_antiCheatValue = m_jumpRelatedAC2;

	bool holdingLeft = m_holdingLeft;
	bool holdingRight = m_holdingRight;

    if (m_holdingLeft && m_holdingRight) {

        if (m_leftPressedFirst)
            holdingRight = false;
        else
            holdingLeft = false;
    }

    if (m_isPlatformer && m_isOnSlope) {
        float slopeAngleDeg = fabsf(CC_RADIANS_TO_DEGREES(m_slopeAngleRadians));
        if (slopeAngleDeg >= 80.0f || slopeAngleDeg >= 40.0f && m_currentSlope->m_isIceBlock)
            m_canJump = false;
    }

    m_antiCheatValue = m_canJump ? 213 : 0;

	bool couldJump = m_canJump;
	bool isHoldingJump = m_holdingJump;

    if (m_isRobot && !m_isJumpUnused)
        isHoldingJump = false;

	float gravity = (m_isBall || isFlying() || m_isSpider)
					? 0.958199f  // ship, UFO, wave, swing, ball, spider
					: m_gravity; // cube, robot

	float modifiedGravity = (m_gravityMod != 1.0f)
					? gravity * m_gravityMod
					: gravity;

	float scaleMod = (m_playerScale == 1.0f) ? 1.0f : 0.8f;

	// flying game mode physics (ship, UFO, wave, swing)
    if (isFlying()) {

        if (m_playerScale != 1.0f)
            scaleMod = 0.85f;

        float maxYVel =  8.0f / scaleMod;
        float minYVel = -6.4f / scaleMod;

		bool shouldRecapVelocity = false;
		if (!m_isUpsideDown) {
			if ((m_yVelocity >= 0.0f && m_yVelocity < maxYVel) || (m_yVelocity <= 0.0f && m_yVelocity > minYVel))
				shouldRecapVelocity = true;			
		}
		else {
			if ((m_yVelocity <= 0.0f && m_yVelocity > -maxYVel) || (m_yVelocity >= 0.0f && m_yVelocity < -minYVel))
				shouldRecapVelocity = true;
		}

		// reapply terminal velocity cap if it
		// has been uncapped by certain orbs or pads (ex.: red orb/pad, black orb)
		if (shouldRecapVelocity)
			m_isVelocityUncapped = false;

		if (m_isShip) {

			float shipMod = 1.0f;

			if (m_holdingJump && !m_isVelocityUncapped)
				shipMod = -1.0f;
			else {

				if (m_isVelocityUncapped)
				{
					if (m_isUpsideDown)
						shipMod = (m_yVelocity > 0.0f) ? -1.0f : 0.8f;
					else
						shipMod = (m_yVelocity < 0.0f) ? -1.0f : 0.8f;
				}
				else shipMod = 0.8f;

				if (!m_holdingJump && !playerIsFallingBugged())
					shipMod = 1.2f;
			}
			if (m_isPlatformer) modifiedGravity *= 0.8f;
			if (shipMod >= 0.0f) gravity = modifiedGravity;

			float boostMod = (m_holdingJump && playerIsFallingBugged())
								? 0.5f
								: 0.4f;

			addToYVelocity( -((gravity * dt * flipMod() * shipMod * boostMod) / scaleMod), 64);

			if (m_holdingJump) m_onGround = false;

			if (m_gameLayer && m_wasHoldingJump != m_holdingJump) {
				if (m_holdingJump)
					gameEventTriggered(static_cast<int>(GJGameEvent::ShipBoostStart), 0);
				else
					gameEventTriggered(static_cast<int>(GJGameEvent::ShipBoostEnd), 0);				
			}
		}
		else if (m_isBird) {

			if (m_isJumpUnused && m_holdingJump) {
				m_isJumpUnused = false;

				float birdScaleMod = (m_playerScale == 1.0f) ? 7.0f : 8.0f;
				double birdJumpVel = (birdScaleMod * flipMod() * scaleMod);

				if (
					( m_isUpsideDown && birdJumpVel < m_yVelocity) ||
					(!m_isUpsideDown && birdJumpVel > m_yVelocity)
				) {
					setYVelocity(birdJumpVel, 7);

					if (m_wasOnSlope || m_isOnSlope) {

						if ( m_slopeVelocity > 0.0 ) {

							double max = m_yVelocity * 1.4f;

							addToYVelocity(m_slopeVelocity * 0.5f, 8);
							setYVelocity(std::min(m_yVelocity, max), 9);
						}
					}
				}

				playBurstEffect();

				if (m_gameLayer)
					gameEventTriggered(static_cast<int>(GJGameEvent::UFOJump), 0);				
			}

			float birdMod = playerIsFallingBugged() ? 0.8f : 1.2f;
			addToYVelocity( -((modifiedGravity * dt * flipMod() * birdMod * 0.5f) / scaleMod), 66);

			if (m_holdingJump) m_onGround = false;
		}
		else if (m_isDart) {

			float dirMod = m_holdingJump ? 1.0f : -1.0f;
			setYVelocity(flipMod() * 8.0f * dirMod, 11);

			double xVelocity = m_playerSpeed * m_speedMultiplier;
			float dirMod2 = m_holdingJump ? 1.0f : -1.0f; // why?

			setYVelocity(xVelocity * flipMod() * dirMod2, 12);

			if (m_gameLayer && m_wasHoldingJump != m_holdingJump) {
				if (m_holdingJump)
					gameEventTriggered(static_cast<int>(GJGameEvent::WavePush), 0);
				else
					gameEventTriggered(static_cast<int>(GJGameEvent::WaveRelease), 0);
			}
		}
		else if (m_isSwing) {

			if (m_isJumpUnused && m_holdingJump)
			{
				m_isJumpUnused = false;
				float preFlipYVelocity = m_yVelocity;

				flipGravity(!m_isUpsideDown, true);
				setYVelocity(preFlipYVelocity * 0.8f, 10);

				if (m_gameLayer) gameEventTriggered(static_cast<int>(GJGameEvent::SwingSwitch), 0);
			}

			float swingScaleMod = (m_playerScale == 1.0f) ? 0.4 : 0.6;
			addToYVelocity(-(swingScaleMod * (modifiedGravity * dt * flipMod())), 67);

			if (m_holdingJump) m_onGround = false;
			scaleMod = 1.0f;
		}

		float modeScale = m_isSwing ? 1.0f : 0.8f;

		// terminal velocity clamping for ship, UFO, and swing
        if (!m_isVelocityUncapped && !m_isDart) {
			if (!m_isUpsideDown) {
				setYVelocity(std::max(m_yVelocity, static_cast<double>(modeScale * -8.0f / scaleMod)), 13);
				setYVelocity(std::min(m_yVelocity, static_cast<double>(8.0f / scaleMod)), 14);
			}
			else {
				setYVelocity(std::max(m_yVelocity, static_cast<double>(-8.0f / scaleMod)), 15);
				setYVelocity(std::min(m_yVelocity, static_cast<double>(modeScale * 8.0f / scaleMod)), 16);
			}
		}
		
		if (playerIsFallingBugged())
			m_isJumping = false;
    }
	else { 
		// ground mode physics block (cube, ball, robot, spider)

		float groundModeGravityScale = 1.0f;
		if (m_isBall || m_isSpider || m_isSwing) // m_isSwing ? bruh
			groundModeGravityScale = 0.6f;
		else if (m_isRobot)
			groundModeGravityScale = 0.9f;


		bool isSlopeForcedMovement;
		bool canJumpDuringSlopeForce;

		if ((m_slopeForceLeft && !holdingLeft) || (m_slopeForceRight && !holdingRight)) {
			if (m_isSlidingRight != m_slopeForceLeft && !m_isSlopeUphillRelative)
				m_slopeSlideTimer = m_isSlopeUphillRelative;

			isSlopeForcedMovement = true;
			canJumpDuringSlopeForce = m_slopeSlideTimer <= 1;
		} else {
			isSlopeForcedMovement = false;
			canJumpDuringSlopeForce = true;
		}

		if (isHoldingJump && m_canJump)
		{
			if (m_isSpider && !m_isDashing) {
				spiderTestJump(false);
			}
			else if (!m_isDashing && (!m_isPlatformer || canJumpDuringSlopeForce)) {

				m_isJumping = true;
				m_onGround = false;
				m_canJump = false;
				m_isJumpUnused = false;
				m_touchedPad = false; // this too
				m_accelerationOrSpeed = 0.0; // TODO: find real name...

				if (!m_slopeForceLeft && !m_slopeForceRight && m_slopeSlideTimer > 0)
				{
					m_slopeSlideTimer = 0;
					m_slopeForceEndTime = m_totalTime;
				}

				float jumpVelocity = m_yStart;

				if (m_isRobot)
					jumpVelocity *= 0.5f;

				bool triggeredAntiCheat = false;
				if (m_antiCheatValue != 213)
				{
					triggeredAntiCheat = true;
					jumpVelocity = 9999.0f;
					m_isVelocityUncapped = true;
				}

				if (m_isPlatformer && isSlopeForcedMovement) {

					if (m_isMoving) {
						double xVelocity = m_playerSpeed * m_speedMultiplier;
						if (fabs(m_platformerXVelocity) > xVelocity) {
							jumpVelocity += fabs(m_platformerXVelocity) / xVelocity;
						}
					}
					else if (m_slopeSlideTimer > 0) {
						jumpVelocity *= (1.0f - (m_slopeSlideTimer * 0.3f));
					}

					m_slopeSlideTimer++;
				}

				setYVelocity(((jumpVelocity * flipMod()) * scaleMod), 2);
				if (m_wasOnSlope || m_isOnSlope) {

					if (m_slopeVelocity * flipMod() > 0.0f) {

						if (!m_isPlatformer || fabs(m_platformerXVelocity) > 4.0f) {

							double threshold = m_yVelocity * 1.4f;
							float modifiedSlopeYVel = getModifiedSlopeYVel();

							if (m_isBall) modifiedSlopeYVel = m_slopeVelocity;
							
							addToYVelocity(modifiedSlopeYVel * 0.25f, 60);

							if (!m_isUpsideDown)
								setYVelocity(std::min(m_yVelocity, threshold), 3);
							else
								setYVelocity(std::max(m_yVelocity, threshold), 4);
						}
					}
				}
				m_shouldTryPlacingCheckpoint = true;

				// WARNING: this timestamp method is not 100% equivalent. Please
				// look into _ftime64 for exactness if truly needed.
				auto now = std::chrono::system_clock::now().time_since_epoch();
				double seconds = std::chrono::duration<double>(now).count();
				m_lastJumpTime = std::floor(seconds * 1000.0) / 1000.0;

				incrementJumps();

				if (m_isBall) {

					flipGravity(!m_isUpsideDown, true);
					m_yVelocity *= 0.6f;
					m_isGroundTouchSideValid = false;
					m_holdingJump = false;
				}
				else if (!m_isRobot && !m_isSpider)
					runRotateAction(true, 11);

				if (m_isRobot)
					m_robotSprite->tweenToAnimation("jump_loop", 0.1f);

				if (m_gameLayer) {
					bool isCube = isInNormalMode();

					if (isCube)           gameEventTriggered(static_cast<int>(GJGameEvent::NormalJump), 0);
					else if (m_isRobot)   gameEventTriggered(static_cast<int>(GJGameEvent::RobotBoostStart), 0);
					else if (m_isBall)    gameEventTriggered(static_cast<int>(GJGameEvent::BallSwitch), 0);					
				}

				#ifdef GEODE_IS_ANDROID

				if (!triggeredAntiCheat && !couldJump) {
					const char* kGVCheckIfServerOnline = "0055";
					GM->setGameVariable(kGVCheckIfServerOnline, true);				
				}

				#endif

				if (m_isPlatformer) animatePlatformerJump(1.0f);
			}
		}
		else {
			if (m_isJumping) {

				if (m_isRobot && m_holdingJump && !m_touchedPad) {
					if ( m_accelerationOrSpeed < 1.5f ) {
						m_accelerationOrSpeed += dt * 0.1f;
						addToYVelocity(modifiedGravity * dt * flipMod() * groundModeGravityScale, 61);
					}
				}

				addToYVelocity(-(groundModeGravityScale * modifiedGravity * dt * flipMod()), 62);

				if (m_isRobot && m_touchedPad && !m_wasRobotJump && m_gameLayer)
					gameEventTriggered(static_cast<int>(GJGameEvent::RobotBoostStop), m_wasRobotJump);

				if (playerIsFallingBugged() || m_isPlatformer && !playerIsMovingUp() )
				{
					m_isJumping = false;
					m_onGround = false;
					m_maybeIsFalling = true;
					m_fallStartY = getPosition().y;

					if (m_isRobot) {

						m_robotSprite->tweenToAnimation("fall_loop", 0.1f);
						if (!m_touchedPad && m_gameLayer)
						gameEventTriggered(static_cast<int>(GJGameEvent::RobotBoostStop), m_touchedPad);
					}
					else if (m_isSpider) {

						m_spiderSprite->tweenToAnimation("fall_loop", 0.1f);
					}
					
				}
			}
			else {
				if (m_canJump)
					m_fallStartY = getPosition().y;

				if (playerIsFallingBugged() && (!m_isPlatformer || m_totalTime - m_lastLandTime >= 0.050000004f || !canJumpDuringSlopeForce)) {
					m_canJump = false;
				}

				addToYVelocity(-(groundModeGravityScale * modifiedGravity * dt * flipMod()), 63);

				// terminal velocity clamping for cube, ball, robot, and spider
				if (!m_isUpsideDown)
					setYVelocity(std::max(m_yVelocity, -15.0), 5);
				else
					setYVelocity(std::min(m_yVelocity, 15.0), 6);

				if (playerIsFalling(-0.25f)
				&& !m_isBall
				&& !m_isSpider
				&& !m_isRobot
				&& !m_isRotating
				&& !m_isOnSlope
				&& !m_isCollidingWithSlope
				&& (!m_isPlatformer || !m_onGround) )
				{
					runRotateAction(true, 12);
				}

				if (playerIsFallingBugged()) {

					if (m_isUpsideDown ? m_yVelocity > 4.0f : m_yVelocity < -4.0f)
					{                              // TODO: find name ↓
						if (m_isRobot && m_onGround && !m_maybeSpriteRelated) {
							m_robotSprite->tweenToAnimation("fall_loop", 0.1f);
						}
						else if (m_isSpider && m_onGround && !m_maybeSpriteRelated)
							m_spiderSprite->tweenToAnimation("fall_loop", 0.1f);
						m_onGround = false;
					} 
				}
			}							
		}
	}

	m_wasHoldingJump = m_holdingJump;
    m_wasRobotJump = m_touchedPad; // TODO: rename these
}