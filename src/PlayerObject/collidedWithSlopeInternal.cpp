/*
	====== PlayerObject::collidedWithSlopeInternal ======
	
	This function is the responsible for the entirety of 
	Geometry Dash's slope physics. It runs every frame that
	the player is considered close enough to a slope, handling
	everything from stickiness on downward slopes to the
	rotation speed of the Ball game mode based on incline.
	
*/
void PlayerObject::collidedWithSlopeInternal(float dt, GameObject *object, bool forced)
{

	// Exit early if we hit the walls of the slope
	// to prevent the player from teleporting unexpectedly
    if (!forced && preSlopeCollision(dt, object)) {
        return;
    }

	// rename incorrect geode bindings
	bool& m_holdingJump = m_jumpBuffered;
	bool& m_isJumping = m_maybeIsBoosted;
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	bool& m_isLastSlopeTop = m_isCurrentSlopeTop;
	double& m_lastSlopeYVelocity = m_currentSlopeYVelocity;
	float& m_playerScale = m_vehicleSize;
	bool& m_ignoreDamagePlayLayer = m_maybeCanRunIntoBlocks;
	bool& m_ignoreDamageEditor = m_ignoreDamage;
	bool& m_tookDamage = m_maybeIsColliding;
	bool& m_slopeWasClampedMax = m_unk3e0;
	bool& m_slopeWasClampedMin = m_unk3e1;
	bool& m_isGoingDownSlope = m_slopeFlipGravityRelated;
	double& m_slopeYOffset = unk_584;
	double& m_lastSlopeYPos = m_unk3d0;
	double& m_lastSlopeYPosRotated = m_blackOrbRelated;
	int& m_slopeSlideTimer = m_maybeSlidingTime;
	bool& m_hitSlopeTop = m_maybeUpsideDownSlope;
	bool& m_isSlopeUphillRelative = m_slopeSlidingMaybeRotated;
	std::unordered_map<int, GameObject*>& m_preSlopeObjects = m_potentialSlopeMap;
	std::unordered_map<int, GJPointDouble>& m_rotatedObjectDeltas = m_rotateObjectsRelated;
	

	CCRect playerRect = getObjectRect();
	CCRect slopeRect = object->getObjectRect();

    bool isUphill = object->m_slopeUphill;
    bool slidingDown = !isUphill;

	// Platformer uses the velocity for movement direction since m_isGoingLeft
	// is input based in Platformer and doesn't account for external forces
	bool isMovingLeft = (!m_isPlatformer && m_isGoingLeft) || (m_isPlatformer && m_platformerXVelocity < 0.0);

    if (isMovingLeft) slidingDown = !slidingDown;

    bool isFloorTop = object->slopeFloorTop();
    bool backwardsRamp = false;
    bool movingBackwards = false;

	CCPoint slopePosDelta = object->getRealPosition() - object->getLastPosition();
	float slopeDeltaX = m_isSideways ? slopePosDelta.y : slopePosDelta.x;
	float slopeDeltaY = m_isSideways ? slopePosDelta.x : slopePosDelta.y;

	double playerDeltaX = m_playerSpeed * m_speedMultiplier * dt;
	bool slopeFasterThanPlayer = slopeDeltaX > playerDeltaX;

    if (slopeFasterThanPlayer) {
		backwardsRamp = (!m_isUpsideDown && slidingDown) || (m_isUpsideDown && !slidingDown);
        movingBackwards = true;
		slidingDown = !slidingDown;
    }

	if (m_isUpsideDown != m_isSideways) slidingDown = !slidingDown;

	// "Give slide up priority over slide down"
	// - RobTop Games
    if (
		m_wasOnSlope &&
		m_slopeVelocity * flipMod() > 0.0f &&
		slidingDown &&
		m_isLastSlopeTop == isFloorTop &&
		m_isLastSlopeTop == m_isUpsideDown
	) {
		return;
    }

	float newSlopeYVelocity = slopeRect.size.height / slopeRect.size.width / (m_playerSpeed * m_speedMultiplier);
	
	if (
		m_wasOnSlope &&
		m_slopeVelocity * flipMod() > 0.0f &&
		m_lastSlopeYVelocity > newSlopeYVelocity
	) {
		return;
	}

	// Compute slide stickiness from slidingDown;
	// evaluates to 1.0 if true. Used to stick to 
	// downward slopes.
    float slideStickiness = slidingDown;
    if (m_wasOnSlope) slideStickiness = slidingDown * 4;
	
	float slopeYDiff = m_isSideways
		? object->getRealPosition().x - object->getLastPosition().x
		: object->getRealPosition().y - object->getLastPosition().y;
	
	bool isMovingDown = (!m_isUpsideDown && slopeYDiff > 0.0f) || (m_isUpsideDown && slopeYDiff < 0.0f);
	
	// Extend the stickiness factor if the slope is actively moving down
	// to keep the player on the slope
	if (forced || isMovingDown) {
		slopeYDiff = fabs(slopeYDiff);
		slopeYDiff = MIN(slopeYDiff, (m_isPlatformer ? kStickDistancePlatformer : kStickDistance) * dt);
		slideStickiness += slopeYDiff;
	}

    float playerRadius = playerRect.size.height * 0.5f;
	
    float cosTargetAngle = cosf(m_slopeRotation);
    float playerH = playerRadius / cosTargetAngle;
	float playerFeet = 0.0f;

    if (!m_isUpsideDown)
        playerFeet = (getPosition().y - playerH) - slideStickiness;
    else
        playerFeet = (getPosition().y + playerH) + slideStickiness;

    if (!m_wasOnSlope) {
        CCRect rect = CCRectMake(
									slopeRect.origin.x,
									slopeRect.origin.y + 1.0f,
									slopeRect.size.width,
									slopeRect.size.height - 2.0f
									);

        if (!playerRect.intersectsRect(rect)) {
            return;
        }
    }
    else if (!m_isUpsideDown && (slopeRect.origin.y + slopeRect.size.height < playerFeet))
		return;
    else if (m_isUpsideDown && (slopeRect.origin.y > playerFeet))
		return;


    CCPoint playerPos = getPosition();

    float slopeMinY = slopeRect.getMinY();
    float slopeMaxY = slopeRect.getMaxY();

	float toleranceValue = 20;
	float slopeAngle = object->getSlopeAngle();
    float playerSlopeOffset = (playerRect.size.height / cosf(slopeAngle)) * 0.5f;

    float slopeTolerance = 0.0f;
	bool slopeIntersection = m_wasOnSlope &&
							 m_collidingWithSlopeId != object->m_uniqueID &&
							 m_isLastSlopeTop != isFloorTop;

	if (slopeIntersection) slopeTolerance = m_isPlatformer ? 0.0f : toleranceValue * m_playerScale;

    float slopeYPos = object->slopeYPos(playerPos.x);
    bool wasMin = false;
	bool wasMax = false;
	
	// Add the player's Y offset to the slope Y and clamp
	// to get the final position
    if (!isFloorTop) {
        float maxYPos = (playerRadius + slopeMaxY) - slopeTolerance;

        slopeYPos = (slopeYPos + playerSlopeOffset) - slopeTolerance;
		if (slopeYPos >= maxYPos) {
            slopeYPos = maxYPos;
			wasMax = true;
        }

		if (slopeYPos <= slopeMinY) {
            slopeYPos = slopeMinY;
			wasMin = true;
        }
    }
    else {
        float minYPos = (slopeMinY - playerRadius) + slopeTolerance;

        slopeYPos = (slopeYPos - playerSlopeOffset) + slopeTolerance;
        if (slopeYPos <= minYPos) {
			slopeYPos = minYPos;
			wasMax = true;
		}

        if (slopeYPos >= slopeMaxY) {
            slopeYPos = slopeMaxY;
			wasMin = true;
        }
    }

	bool collide = false;
    bool didHitTop = false;
	bool dontHitGround = false;
    bool knockDown = false;
	bool pushUp = false;

	// Case 1: landing on a slope with correct gravity
	if (m_isUpsideDown == isFloorTop) {	
		bool special = !slopeIntersection && slidingDown && !m_isOnSlope && (!m_isJumping || isFlying()) && (!m_isShip || !m_holdingJump);

		if (forced && ! slidingDown) special = true;
		if (!slidingDown && isMovingDown) special = true;

		bool touchingNormally = m_isUpsideDown ? (playerPos.y > slopeYPos) : (playerPos.y < slopeYPos);

		if (!m_isUpsideDown)
			collide = touchingNormally || (special && playerPos.y < slopeYPos + slideStickiness && (!m_isBird || m_yVelocity <= 0.0f));
		else
			collide = touchingNormally || (special && playerPos.y > slopeYPos - slideStickiness && (!m_isBird || m_yVelocity >= 0.0f));

		pushUp = m_holdingJump && isFlying() && (!slidingDown || m_isPlatformer);
		dontHitGround = pushUp && (!m_isPlatformer || !slopeIntersection);

		isMovingDown = false;
	}
	// Case 2: player hit the underside of a slope
    else {
        didHitTop = true;

		if (slidingDown) slideStickiness = 0.0f;
		else if (isFlying() && m_holdingJump) slideStickiness = m_wasOnSlope ? 2.0f : 1.0f;

		bool special = !slopeIntersection && (!isFlying() || !slidingDown || m_isPlatformer) && !m_isOnSlope;
		bool touchingNormally = m_isUpsideDown ? (playerPos.y < slopeYPos) : (playerPos.y > slopeYPos);
	
        if (!m_isUpsideDown)
			collide = touchingNormally || (special && playerPos.y > slopeYPos - slideStickiness);
        else
			collide = touchingNormally || (special && playerPos.y < slopeYPos + slideStickiness);

        dontHitGround = !m_holdingJump && !m_isPlatformer && (isFlying() || m_isBall) && slidingDown && m_wasOnSlope;
        if (isFlying() && !m_holdingJump && slidingDown) knockDown = true;
		
        // Player should crash if he hits head on a slope
        if (collide) {
            if (!isFlying() && !m_isBall && !m_isPlatformer && m_stateHitHead < 1) {
				// Cube, Spider, and Robot handled here

				bool safe = isSafeMode(0.1f) || isSafeFlip(0.1f);
				bool dontManipulate = false;

				if (!safe) {
					float headHitTolerance = 2.0f;
					if (!m_isUpsideDown)
						collide = playerPos.y - headHitTolerance > slopeYPos;
					else
						collide = playerPos.y + headHitTolerance < slopeYPos;

					safe = !collide;
					dontManipulate = true;
				}

				if (!safe) {
					m_canJump = false;
					m_onGround = false;
					if (!m_ignoreDamageEditor) {
						if (m_ignoreDamagePlayLayer) {
							m_tookDamage = true;
							return;
						}
						else {
							PL->destroyPlayer(this, NULL);
							return;
						}
					}
				}
				else {
					if (!dontManipulate) {
						setPosition(ccp(getPosition().x, slopeYPos));
						setYVelocity(!m_isUpsideDown ? MIN(m_yVelocity, -2.0) : MAX(m_yVelocity, 2.0), 0);
					}
					m_canJump = false;
					m_onGround = false;
					return;
				}
            }
            else {
                isMovingDown = knockDown;
            }

			knockDown = isMovingDown;
			bool dontCrash =
				(!object->m_slopeIsHazard && ((!slopeIntersection && (!m_isDart || m_stateDartSlide > 0)) ||
				(m_isPlatformer || m_stateHitHead > 0))) ||
				m_ignoreDamageEditor;

			if (!dontCrash) {
				if (m_ignoreDamagePlayLayer) { // Also true in the editor
					m_tookDamage = true;
					return;
				}

				PL->destroyPlayer(this, NULL);
				return;
			}
        }
    }

	float slopeYPosAdjusted = slopeYPos;
    if (m_isSideways) {
		int slopeUniqueID = object->m_uniqueID;

		auto it = m_rotatedObjectDeltas.find(slopeUniqueID);
		if (it != m_rotatedObjectDeltas.end()) {

			GJPointDouble& entry = m_rotatedObjectDeltas[slopeUniqueID];
        	slopeYPosAdjusted -= entry.m_y;
		}
	}

	bool moving = !m_isPlatformer || (fabs(m_platformerXVelocity) >= 0.1f);
	if (m_wasOnSlope && moving) {

		bool isInvalidPos = (m_lastSlopeYPos == slopeYPos) || 
							(m_isSideways && m_lastSlopeYPosRotated == slopeYPosAdjusted);

		bool isClamped = (wasMax && m_slopeWasClampedMax) || (wasMin && m_slopeWasClampedMin);
		bool isValidSlopeMove = (slopeDeltaY != 0.0f) && isClamped && !m_isDashing &&
                         (!m_isPlatformer || fabs(m_platformerXVelocity) > 0.1f);


		if (isInvalidPos || isValidSlopeMove) {
			collide = false;
		}
	}
			
	// Test collision with a widened player hitbox in Platformer,
	// exit if we aren't near the slope at all
    if (m_isPlatformer && collide) {
        CCRect extendedPlayerRect = CCRectMake(
								playerRect.origin.x - 2.0f,
								playerRect.origin.y - 10.0f,
								playerRect.size.width + 4.0f,
								playerRect.size.height + 20.0f
								);

        if (!slopeRect.intersectsRect(extendedPlayerRect)) {
            collide = false;
        }
    }

	// Exit if Dart mode and moving away from the slope
    if (slidingDown && m_isDart && m_holdingJump && isFloorTop == m_isUpsideDown) {
        return;
    }

    if (!collide) {
        return;
    }

    m_currentSlope = object;
    m_slopeAngleRadians = object->getSlopeAngle();
    m_currentPotentialSlope = m_currentSlope;
	m_preSlopeObjects[object->m_uniqueID] = object;
    m_slopeYOffset = playerSlopeOffset - playerRadius;
    m_isCurrentSlopeTop = isFloorTop;
    m_lastSlopeYPos = slopeYPos;
    m_lastSlopeYPosRotated = slopeYPosAdjusted;
    m_collidingWithSlopeId = object->m_uniqueID;
    m_isGoingDownSlope = slidingDown;
    m_slopeWasClampedMax = wasMax;
    m_slopeWasClampedMin = wasMin;
	double previousTargetSlopeAngle = m_slopeRotation;

	int yDirMod = slidingDown ? flipMod() : -flipMod();
	int dirMod  = movingBackwards ? -yDirMod : yDirMod;
	int xDirMod = isMovingLeft ? -dirMod : dirMod;
	int sidewaysMod = m_isSideways ? -xDirMod : xDirMod;

	// Why did RobTop not just do sidewaysMod * slopeAngle...
    m_slopeRotation = (sidewaysMod * CC_DEGREES_TO_RADIANS(CC_RADIANS_TO_DEGREES(slopeAngle)));//   uh idk ↓

    this->setPosition(ccp(this->getPosition().x, slopeYPos));

    m_isOnSlope = true;

    if (!m_wasOnSlope) {
        m_slopeStartTime = m_totalTime;
        m_yVelocityBeforeSlope = m_yVelocity;
    }

    m_hitSlopeTop = didHitTop;

	bool landedCorrectSide = !didHitTop;
    if (!dontHitGround) {
        if (landedCorrectSide) {
            float yVel = m_yVelocity;
            hitGround(object, false);

            if (
				(!m_isUpsideDown && yVel > 5.0f) ||
				(m_isUpsideDown && yVel < -5.0f)
			) {
                setYVelocity(yVel, 0);
            }

			bool platformerShouldSlide = fabs(CC_RADIANS_TO_DEGREES(m_slopeAngleRadians)) > 40.0f;
			
            if (m_isPlatformer && platformerShouldSlide && yVel < -5.0f && m_platformerXVelocity > 0.0f) {
                m_platformerXVelocity *= 0.5f;
            }

            updateCollide(PlayerCollisionDirection::Bottom, object);

			
            m_currentSlope2 = object; // Unsure about name

            m_slopeAngle = object->getSlopeAngle();
			bool uphill = m_currentSlope2->m_slopeUphill;

            m_isSlopeUphillRelative = uphill;

            if (m_isSideways)
                m_isSlopeUphillRelative = !uphill;

            if (m_isSlopeUphillRelative && m_slopeAngle >= 1.0f)
                m_slopeSlideTimer = 3;

			CCPoint slopeLastPos = object->getLastPosition();
			CCPoint slopeCurrPos = object->getRealPosition();
			bool slopeMoved = (slopeCurrPos.x != slopeLastPos.x) || (slopeCurrPos.y != slopeLastPos.y);

            if (slopeMoved) {
				bool posUnchanged = false;
				bool posDecreased = false;
				float slopeDelta = 0.0f;

                if (!m_isUpsideDown) {
                    posUnchanged = slopeCurrPos.y == slopeLastPos.y;
                    posDecreased = slopeCurrPos.y < slopeLastPos.y;
					slopeDelta = slopeCurrPos.y - slopeLastPos.y;
                }
                else {
                    posUnchanged = slopeLastPos.x == slopeCurrPos.x;
                    posDecreased = slopeLastPos.x < slopeCurrPos.x;
					slopeDelta = slopeCurrPos.x - slopeLastPos.x;
                }

				bool positionIncreased = !posDecreased && !posUnchanged;

                if (positionIncreased) m_groundYVelocity = slopeDelta / dt;
            }
        }
        else {
            double clampedYVel = !m_isUpsideDown ? MIN(m_yVelocity, 0.0) : MAX(m_yVelocity, 0.0);
            setYVelocity(clampedYVel, 0);

            m_canJump = false;
            m_onGround = false;
            updateCollide(PlayerCollisionDirection::Top, object);
        }
    }

    if (knockDown) {
        if (!m_isUpsideDown)
            if (m_yVelocity > -2.0f) setYVelocity(-2.0, 0);
        else
            if (m_yVelocity < 2.0f) setYVelocity(2.0, 0);
    }

    if (pushUp) {
        if (!m_isUpsideDown)
            if (m_yVelocity < 2.0f) setYVelocity(2.0, 0);
        else
            if (m_yVelocity > -2.0f) setYVelocity(-2.0, 0);
    }

    m_lastSlopeYVelocity = newSlopeYVelocity;

    float velocityMagnitude = 1.1f;
	velocityMagnitude = MIN(velocityMagnitude, 0.8f / slopeAngle);
    velocityMagnitude *= newSlopeYVelocity * 1.4f;
    if (slidingDown && !backwardsRamp) velocityMagnitude *= -1;

    m_slopeVelocity = velocityMagnitude * flipMod();

    if (m_isPlatformer && didHitTop && m_isBird) {
        m_holdingJump = false;
    }

	// Cube, Robot, and Spider simply face the slope's angle
    if ((!isFlying() && !m_isBall)) {
        updateSlopeRotation(dt);
    }
    else {
		m_slopeVelocity *= 0.75f;

		if (m_isBall) {
			// Ball mode rotates faster on steeper slopes
			double currentTargetSlopeAngle = m_slopeRotation;
			if (previousTargetSlopeAngle != currentTargetSlopeAngle) {

				float rotationMultiplier = 1.0f / cosf(currentTargetSlopeAngle);
				float max = 2.0f;

				if (rotationMultiplier > max) {
					rotationMultiplier = (rotationMultiplier - 1.0f) * 0.7f + 1.0f;
				}

				stopRotation(false, 0);
				runBallRotation(rotationMultiplier);
			}	
		}
		else updateSlopeRotation(dt);
    }
}