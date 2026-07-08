/*
	====== PLAYEROBJECT::PRESLOPECOLLISION ======

	This function acts as the pre-validator for slope collisions before 
	the actual slope logic runs inside collidedWithSlopeInternal.
	It is called once at the start of collidedWithSlopeInternal and acts as a gate.

	Notably, this function:
	- calls slopeFloorTop and slopeWallLeft to determine the orientation
	  of the flat edges of the slope
	- detects collisions against the flat edges of the slope object
	- reroutes collision to collidedWithObject if there was a collision
	- otherwise returns false and collision continues through collidedWithSlopeInternal
	
*/
bool PlayerObject::preSlopeCollision(float dt, GameObject *object)
{
	auto lastSlopeID = m_collidingWithSlopeId;
    if (object->m_uniqueID == lastSlopeID) {
        return false;
    }

    CCRect slopeRect = object->getObjectRect();
    CCRect playerRect = getObjectRect();

	bool collided = false;
    float xPadding = 0.0f;
    float yPadding = 0.0f;

    if (m_isPlatformer && (m_isOnSlope || m_wasOnSlope)) {
        yPadding = 5.0f;
    }

	CCPoint slopePosDelta = object->getRealPosition() - object->getLastPosition();

	if (m_isSideways) {
		slopePosDelta.x = slopePosDelta.y;
	}

	bool reversed = m_isGoingLeft;
	float xDelta = m_playerSpeed * m_speedMultiplier * dt;

	// Check 1. slope's wall is on the left.
	if (object->slopeWallLeft()) {
		if (!reversed || m_isPlatformer || xDelta > slopePosDelta.x) {
			if (getPosition().x < slopeRect.origin.x) {
				xPadding = (reversed && !m_isPlatformer) ? 1.0f : 0.0f;

				float rectHeight = slopeRect.size.height - (yPadding * 2.0f);
                CCRect wallRect = CCRectMake(slopeRect.origin.x, slopeRect.origin.y + yPadding, 1.0f, rectHeight);

				if (playerRect.intersects(wallRect)) {
					collidedWithObjectInternal(dt, object, wallRect, false);
					collided = true;
				}				
			}
		}
	}

	// Check 2. slope's wall is on the right.
	else {
		if (reversed || m_isPlatformer || xDelta < slopePosDelta.x) {

			if (slopeRect.getMaxX() < getPosition()) {
				xPadding = (!reversed && !m_isPlatformer) ? 1.0f : 0.0f;

				float rectHeight = slopeRect.size.height - (yPadding * 2.0f);
				CCRect wallRect = CCRectMake(slopeRect.getMaxX() - 1.0f, slopeRect.origin.y + yPadding, 1.0f, rectHeight);
				
				if (playerRect.intersects(wallRect)) {
					collidedWithObjectInternal(dt, object, wallRect, false);
					collided = true;
				}	
			}
		}
	}

	// Check 3. slope's flat part is on the top
	if (object->slopeFloorTop()) {

		float rectWidth = slopeRect.size.width - (xPadding * 2.0f);
		CCRect topRect = CCRectMake(slopeRect.origin.x + xPadding, slopeRect.getMaxY() - 1.0f, rectWidth, 1.0f);

		if (getPosition().y >= topRect.getMaxY()) {
			if (playerRect.intersectsRect(topRect)) {
				collidedWithObjectInternal(dt, object, topRect, false);
				collided = true;
			}
		}
	}

	// Check 4. slope's flat part is on the bottom
	else {

		float rectWidth = slopeRect.size.width - (xPadding * 2.0f);
		CCRect bottomRect = CCRect(slopeRect.origin.x + xPadding, slopeRect.origin.y, rectWidth, 1.0f);
		
		if (getPosition().y <= bottomRect.getMaxY()) {
			if (playerRect.intersectsRect(bottomRect)) {
				collidedWithObjectInternal(dt, object, bottomRect, false);
				collided = true;
			}
		}
	}

	// If we are not touching the walls of the slope,
	// add it to the list of slopes that we are near
	// and update the current one.
	if (!collided) {
		m_unk669 = false;

		if (!m_isOnSlope) {
			m_potentialSlopeMap[object->m_uniqueID] = object;
			GameObject* currentPotentialSlope = m_currentPotentialSlope;

			bool shouldUpdateSlope = true;
			
			if (currentPotentialSlope != nullptr) {
				bool potentialIsTop = !currentPotentialSlope->m_slopeUphill || currentPotentialSlope->slopeFloorTop();
				bool currentIsTop = !object->m_slopeUphill || object->slopeFloorTop();

				if (potentialIsTop && currentIsTop) {
					if (object->getPositionY() < currentPotentialSlope->getPositionY()) {
						shouldUpdateSlope = false;
					}
				} else if (!potentialIsTop) {
					if (object->getPositionY() >= currentPotentialSlope->getPositionY()) {
						shouldUpdateSlope = false;
					}
				}
			}

			if (shouldUpdateSlope) {
				m_currentPotentialSlope = object;
			}			
		}
	}

	if (!slopeRect.intersectsRect(playerRect)) return true;

	return collided;
}