#define GM GameManager::sharedState()
#define PL GameManager::sharedState()->getPlayLayer()

/*
	====== PlayerObject::ringJump ======
	
	Ahh, good ol' ringJump...

	This function runs every frame that the player
	is overlapping a jump ring. It handles every game mode,
	all ring mechanics, triggering game events, state updates,
	circle effects, and incrementing the player's jump count,
	all inside one massive function.
	
*/
void PlayerObject::ringJump(RingObject *object, bool skipCheck)
{

    if (m_isDead || object == NULL)
        return;

	// rename misnamed member variables
	std::unordered_set<int>& activatedRingIDs = m_ringRelatedSet;
	bool& m_canRingJump = m_stateRingJump2;
	bool& m_ringJumpingThisTick = m_ringJumpRelated;
	bool& m_holdingJump = m_jumpBuffered;
	bool m_holdingJumpReleaseDelayed = (bool)m_stateJumpBuffered;
	bool& m_touchedTeleportRing = m_touchedGravityPortal;
	bool& m_canDisableAutoJump = m_padRingRelated;
	bool& m_isJumpUnused = m_stateRingJump;
	bool& m_isJumping = m_maybeIsBoosted;
	bool& m_isVelocityUncapped = m_isAccelerating;
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	bool& m_isInPlayLayer = m_playEffects;
	bool& m_isRespawning = m_maybeReducedEffects;
	bool& m_isInEditor = m_editorEnabled;
	float m_playerScale = m_vehicleSize;
	bool& m_2p2ChangesDisabled = m_enable22Changes;

	if (activatedRingIDs.find(object->m_uniqueID) != activatedRingIDs.end())
		return;

    bool ringHasNoEffects = object->m_hasNoEffects;
    GameObjectType ringObjectType = object->getType();
	bool m_isJumpingRing = (ringObjectType != GameObjectType::CustomRing) && (ringObjectType != GameObjectType::TeleportOrb);

    if (!m_canRingJump || m_isDashing)
        return;

	// A ringJump exclusive flag that mirrors m_holdingJump (m_jumpBuffered) with
	// a one frame delay only on release... weird.
    if (!m_holdingJumpReleaseDelayed) {
        return;
    }

    if ((m_touchedRing || !m_isJumpingRing) && (m_touchedCustomRing || ringObjectType != GameObjectType::CustomRing)) {
        if (m_touchedTeleportRing)
            return;

        if (ringObjectType != GameObjectType::TeleportOrb)
            return;
    }

    if (object->m_isReverse) reversePlayer(object);

    m_ringJumpingThisTick = true;

    int ringUniqueID = object->m_uniqueID;
    activatedRingIDs.insert(ringUniqueID);

    if (m_gameLayer != NULL) {
        gameEventTriggered((int)GJGameEvent::OrbActivated, 0);
        GJGameEvent ringEvent = m_gameLayer->objectTypeToGameEvent((int)ringObjectType);
		gameEventTriggered((int)ringEvent, 0);
    }

    if (ringObjectType == GameObjectType::CustomRing)
        m_touchedCustomRing = true;
    else if (ringObjectType == GameObjectType::TeleportOrb)
        m_touchedGravityPortal = true;
    else
        m_touchedRing = true;

    m_touchingRings->removeObject(object, true);

    if (m_isJumpingRing) {
		m_canDisableAutoJump = true;
    }

    if (ringObjectType == GameObjectType::CustomRing) {
		m_gameLayer->activateCustomRing(object);
        if (m_2p2ChangesDisabled)
            m_isJumpUnused = false;
    }
    else if (ringObjectType == GameObjectType::TeleportOrb) {
        m_gameLayer->teleportPlayer((TeleportPortalObject*)object, this);
        m_isJumpUnused = false;
    }
    else if (ringObjectType == GameObjectType::SpiderOrb) {
        if (!m_isSideways) {
            if (object->isFacingDown() != m_isUpsideDown) {
                flipGravity(!m_isUpsideDown, true);
            }
        }
        else {
            if (object->isFacingLeft() != m_isUpsideDown) {
				flipGravity(!m_isUpsideDown, true);
			}
        }
        spiderTestJump(false);
    }
    else if (ringObjectType == GameObjectType::DashRing) {
        if (m_gameLayer != NULL)
			gameEventTriggered((int)GJGameEvent::DashOrb, 0);

		startDashing((DashRingObject*)object);
    }
	else if (ringObjectType == GameObjectType::GravityDashRing) {
		if (!m_isInPlayLayer) {
			LevelEditorLayer* levelEditorLayer = GM->m_levelEditorLayer;

			if (levelEditorLayer == NULL)
				flipGravity(!m_isUpsideDown, true);
			else
				levelEditorLayer->flipGravity(this, !m_isUpsideDown, true);
		}
		else {
			PL->flipGravity(this, !m_isUpsideDown, true);
			PL->playGravityEffect(m_isUpsideDown);
		}

		if (m_gameLayer != NULL)
			m_gameLayer->gameEventTriggered(GJGameEvent::GravityDashOrb, 0, m_uniqueID);

		startDashing((DashRingObject*)object);
	}
	else if (ringObjectType == GameObjectType::DropRing) {
		m_isJumpUnused = false;
		float yVel = flipMod() * -15.0f;

		if (!isFlying()) {
			if (!m_isRobot && m_isSpider) yVel *= 1.1f;
		}
		else {
			yVel = flipMod() * -14.0f;
			if (m_isBird) yVel *= 0.8f;
		}

		setYVelocity(yVel, 0);

		if (m_isBall) runBallRotation2();
		else runRotateAction(false, 0);

		activateStreak();
		m_hasEverHitRing = true;
		m_isVelocityUncapped = true;

		if ((m_isBall) || (m_isSwing)) {
			m_holdingJump = false;
		}
	}
	else {
		// Yellow, pink, red, green, and blue rings are handled here.

		m_isJumpUnused = false;
		m_isJumping = true;
		m_onGround = false;
		m_canJump = false;

		float scaleMod = (m_playerScale == 1.0f) ? 1.0f : 0.8f;
		float finalYVelocity = m_yStart;

		if (ringObjectType == GameObjectType::GravityRing) {
			finalYVelocity *= 0.8f;
		}
		else if (ringObjectType == GameObjectType::GreenRing) {
			if (m_isShip) finalYVelocity *= 0.7f;
		}
		else if (ringObjectType == GameObjectType::PinkJumpRing) {	
			if (m_isShip) finalYVelocity *= 0.37f;
			else if (m_isBird) finalYVelocity *= 0.42f;
			else if (m_isBall) finalYVelocity *= 0.77f;
			else finalYVelocity *= 0.72f;
		}
		else if (ringObjectType == GameObjectType::RedJumpRing) {
			if (m_isShip) finalYVelocity *= (m_playerScale == 1.0f) ? 1.0f : 1.4f;
			else if (m_isBird) finalYVelocity *= (m_playerScale == 1.0f) ? 1.02f : 1.36f;
			else if (m_isBall) finalYVelocity *= 1.34f;
			else if (m_isRobot) finalYVelocity *= 1.28f;
			else if (m_isSpider) finalYVelocity *= 1.34f;
			else finalYVelocity *= 1.38f;
		}
		else if (m_isRobot) {
			finalYVelocity *= 0.9f;
		}

		if (ringObjectType == GameObjectType::GreenRing) {
			if (!m_isInPlayLayer) {
				LevelEditorLayer* levelEditorLayer = GM->m_levelEditorLayer;

				if (levelEditorLayer == NULL)
					flipGravity(!m_isUpsideDown, true);
				else
					levelEditorLayer->flipGravity(this, !m_isUpsideDown, true);
			}
			else {
				PL->flipGravity(this, !m_isUpsideDown, true);
				if (!ringHasNoEffects) PL->playGravityEffect(m_isUpsideDown);
			}
		}

		setYVelocity(flipMod() * finalYVelocity * scaleMod, 0);

		if (m_isBall) runBallRotation2();
		else runRotateAction(false, 0);

		if (m_isPlatformer && !m_isRotating) {
			animatePlatformerJump(1.0f);
		}

		// I'm not sure about "last grounded pos"...
		m_lastGroundedPos = getPosition();
		activateStreak();
		m_hasEverHitRing = true;

		if (m_isBall || m_isSpider) {
			m_yVelocity *= 0.7f;
			m_holdingJump = false;
		}
		else if (m_isSwing) {
			m_yVelocity *= 0.6f;
			m_holdingJump = false;
		}

		if (ringObjectType == GameObjectType::GravityRing) {
			if (!m_isInPlayLayer) {
				LevelEditorLayer* levelEditorLayer = GM->m_levelEditorLayer;

				if (levelEditorLayer == NULL)
					flipGravity(!m_isUpsideDown, true);
				else
					levelEditorLayer->flipGravity(this, !m_isUpsideDown, true);
			}
			else {
				PL->flipGravity(this, !m_isUpsideDown, true);
				if (!ringHasNoEffects) PL->playGravityEffect(m_isUpsideDown);
			}
		}

		if (m_isRobot) {
			m_robotSprite->runAnimation("jump_start");
		}
		else if (m_isSpider) {
			m_spiderSprite->stopTween();
			m_spiderSprite->m_animationManager->stopAnimations();
			m_spiderSprite->tweenToAnimation("jump", 0.06f);
		}

		if (ringObjectType == GameObjectType::RedJumpRing) {
			m_isVelocityUncapped = true;
		}
	}

    if (!m_isRespawning) {
        int playerTouchToggleBlockID = 3643;
        if (
			!GM->m_performanceMode &&
			!object->hasBeenActivated() &&
			m_isInPlayLayer &&
			!ringHasNoEffects &&
			object->m_objectID != playerTouchToggleBlockID
		) {
			ccColor3B effectColor;
			
            switch(ringObjectType) {
				case GameObjectType::PinkJumpRing:
				case GameObjectType::GravityDashRing: effectColor = ccc3(255, 0, 255); break;      // magenta
				case GameObjectType::GravityRing: effectColor = ccc3(0, 255, 255); break;          // cyan
				case GameObjectType::GreenRing:
				case GameObjectType::DashRing: effectColor = ccc3(0, 255, 0); break;               // green
				case GameObjectType::DropRing: {                                                   // light background color
					int lightBgIndex = 1007;
					ccColor3B lightBgColor = PL->m_effectManager->activeColorForIndex(lightBgIndex);
					effectColor = lightBgColor;
					break;					
				}                                                    
				case GameObjectType::RedJumpRing: effectColor = ccc3(255, 100, 0); break;          // orange
				case GameObjectType::CustomRing:                                                   // color inherited from object
					if (object->m_colorSprite != NULL)
						effectColor = object->m_colorSprite->getColor();
					else 
						effectColor = object->getColor();
					break;
				case GameObjectType::SpiderOrb: effectColor = ccc3(255, 50, 255); break;           // pink
				default: effectColor = ccc3(255, 200, 0); break;
            }

			float startRadius = ringObjectType == GameObjectType::RedJumpRing ? 42.0f : 35.0f;
			float endRadius = 5.0f, duration = 0.35f;
			bool fadeIn = true, easeOut = true;

            CCCircleWave* circleEffect = CCCircleWave::create(startRadius, endRadius, duration, fadeIn, easeOut);
            circleEffect->m_color = effectColor;
			circleEffect->setPosition(object->getPosition());
			circleEffect->followObject(object, true);
			circleEffect->m_delegate = PL;

			PL->addCircle(circleEffect);
			m_parentLayer->addChild(circleEffect, 0);
        }
    }

    if (!m_isInEditor)
        object->playTriggerEffect();

    object->activatedByPlayer(this);
    object->powerOffObject();
    incrementJumps();
}
