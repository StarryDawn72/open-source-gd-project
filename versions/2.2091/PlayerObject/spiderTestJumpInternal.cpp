/*
    Landing spot calculation for the spider game mode
    and spider orbs/pads.
*/
void PlayerObject::spiderTestJumpInternal(bool isRetry)
{
    if (m_isDead || m_isLocked || m_isRespawning)
        return;

    float damageCheckWidth = m_playerScale * 8.0f;
    bool notAffectedByDualGrounds = m_isSideways || m_gameLayer->m_gameState.m_isFreeMode || isInBasicMode();

    CCRect playerRect = getObjectRect();
    CCRect solidCheckRect = playerRect;

    float minTeleport = 0.0f;
    float maxTeleport = 0.0f;
    float limit = 100.0f * 30.0f;

    // Teleport limit is 100 blocks in the direction of travel
    // when not affected by ground or ceiling, clamped to
    // the ground Y (90) or world start (0).
    if (m_isSideways) {
        maxTeleport = getPosition().x + limit;
        minTeleport = MAX(0.0f, getPosition().x - limit);
    }
    else if (notAffectedByDualGrounds) {
        minTeleport = MAX(90.0f, getPosition().y - limit);
        maxTeleport = getPosition().y + limit;
    }
    else {
        minTeleport = m_gameLayer->getMinPortalY();
        maxTeleport = m_gameLayer->getMaxPortalY();
    }

    float tolerance = 2.0f;

    // The solidCheckRect is used for the hit test.
    // In normal orientation, the rect stretches from 2 points
    // below the player's head to the max teleport Y,
    // and spans half the player's width - 1.   

    if (!m_isUpsideDown) {
        if (!m_isSideways) {
            float topEdge = solidCheckRect.origin.y + solidCheckRect.size.height - tolerance;
            solidCheckRect.origin.y = topEdge;
            solidCheckRect.size.height = maxTeleport - topEdge;
        }
        else {
            float rightEdge = solidCheckRect.origin.x + solidCheckRect.size.width - tolerance;
            solidCheckRect.origin.x = rightEdge;
            solidCheckRect.size.width = maxTeleport - rightEdge;
        }
    }
    else {
        if (!m_isSideways) {
            float y = solidCheckRect.origin.y;
            solidCheckRect.origin.y = minTeleport;
            solidCheckRect.size.height = (y - minTeleport) + tolerance;
        } else {
            float x = solidCheckRect.origin.x;
            solidCheckRect.origin.x = minTeleport;
            solidCheckRect.size.width = (x - minTeleport) + tolerance;
        }
    }

    // The hazardRect is used to test if a hazard blocks the nearest
    // landing spot. It is the same as the one for solid objects
    // but shifted down to the player's feet, leaving a gap at the top
    // about of about the height of the player hitbox.
    // The width is 8 points for normal size and 4.8 points when mini.
    CCRect hazardRect = solidCheckRect;

    if (!m_isSideways) {
        hazardRect.size.width = playerRect.size.width;
        hazardRect.origin.x = playerRect.origin.x;
    }
    else {
        hazardRect.size.height = playerRect.size.height;
        hazardRect.origin.y = playerRect.origin.y;
    }

    // extraCheckRect is the wider version of solidCheckRect (player width + 4, left-aligned).
    // It's used instead of the normal solid rect if no solids were found but hazards were.

    // The normal solid rect covers only the half of the player in the travel
    // direction (going right: the right half, plus 1 past the edge), so a solid
    // on the trailing half is missed. If a hazard is closer than the
    // landing found with that rect, the function reruns with this wider rect
    // to see whether a solid is actually nearer than the hazard.
    // If the hazard is still closer on the retry, the spider lands on it.

    CCRect extraCheckRect = hazardRect;
    double extraTolerance = 4.0f;

    if (!m_isSideways)
        extraCheckRect.size.width = extraCheckRect.size.width + extraTolerance;        
    else
        extraCheckRect.size.height = extraCheckRect.size.height + extraTolerance;

    if (!m_isSideways) {
        hazardRect.size.width = damageCheckWidth;
        hazardRect.origin.x += (solidCheckRect.size.width - damageCheckWidth) * 0.5f;
    }
    else {
        hazardRect.size.height = damageCheckWidth;
        hazardRect.origin.y += (solidCheckRect.size.height - damageCheckWidth) * 0.5f;
    }

    // more reassigning because robtop is weird and likes messy code
    if (m_isPlatformer) {
        if (!m_isSideways) {
            solidCheckRect.size.width -= 2.0f;
            solidCheckRect.origin.x += 1.0f;
        }
        else {
            solidCheckRect.size.height -= 2.0f;
            solidCheckRect.origin.y += 1.0f;
        }
    }
    else {
        if (!m_isSideways) {
            solidCheckRect.size.width = (playerRect.size.width * 0.5f) + 1.0f;
            solidCheckRect.origin.x = !m_isGoingLeft
                ? playerRect.origin.x + (playerRect.size.width * 0.5f)
                : playerRect.origin.x - (playerRect.size.width * 0.5f) - 1.0f;
        }
        else {
            solidCheckRect.size.height = (playerRect.size.height * 0.5f) + 1.0f;
            solidCheckRect.origin.y = !m_isGoingLeft
                ? playerRect.origin.y + (playerRect.size.height * 0.5f)
                : playerRect.origin.y - (playerRect.size.height * 0.5f) - 1.0f;
        }
    }

    CCArray* staticObjects = m_gameLayer->staticObjectsInRect(solidCheckRect, true);
    CCArray* damagingObjects = m_gameLayer->damagingObjectsInRect(hazardRect, true);

    int (*compareFunc)(const void*, const void*);

    if (m_isSideways)
        compareFunc = !m_isUpsideDown ? boxCompMinX : boxCompMaxX;
    else
        compareFunc = !m_isUpsideDown ? boxCompMin : boxCompMax;

    bool onlyFoundDamagingObjects = staticObjects->count() == 0 && damagingObjects->count() != 0;

    // Skip retry if we only found damaging objects in the way
    if (onlyFoundDamagingObjects || isRetry) {
        isRetry = true;
        staticObjects = m_gameLayer->staticObjectsInRect(extraCheckRect, true);
    }

    // Sort them in order of nearest first so the
    // spider lands on the closest block
    if (staticObjects->count())
        qsort(staticObjects->data->arr, staticObjects->data->num, sizeof(GameObject*), compareFunc);

    if (damagingObjects->count())
        qsort(damagingObjects->data->arr, damagingObjects->data->num, sizeof(GameObject*), compareFunc);

    float prevLandY = 0.0f;
    float landY = 0.0f;
    
    if (onlyFoundDamagingObjects) {
        // Travel only contains hazards; go to it.
        GameObject* nearest = (GameObject*)damagingObjects->objectAtIndex(0);
        CCPoint nearestPos = nearest->getRealPosition();
        landY = !m_isSideways ? nearestPos.y : nearestPos.x;
    }
    else {
        CCPoint playerPos = getPosition();

        int i = 0;
        for (i = 0; i < staticObjects->count(); i++) {

            GameObject* obj = (GameObject*)staticObjects->objectAtIndex(i);
            bool checkingSlope = false;
            
            if (!m_isUpsideDown) {
                CCRect rect = obj->getObjectRect();
                
                if (!m_isSideways)
                    landY = rect.getMinY() - (playerRect.size.height * 0.5f);
                else
                    landY = rect.getMinX() - (playerRect.size.width * 0.5f);
            }
            else {
                CCRect rect = obj->getObjectRect();

                if (!m_isSideways)
                    landY = rect.getMaxY() + (playerRect.size.height * 0.5f);
                else
                    landY = rect.getMaxX() + (playerRect.size.width * 0.5f);
            }

            if (obj->getType() == GameObjectType::Slope) {
                CCPoint pos = obj->getRealPosition();

                if (this->m_isSideways)
                    rotateGameplayObject(obj);

                // Landing on the angled surface of a slope
                if (m_isUpsideDown != obj->slopeFloorTop()) {
                    checkingSlope = true;

                    float slopeY = obj->slopeYPos(playerPos.x);
                    CCPoint slopePos = obj->getRealPosition();

                    if (!m_isSideways)
                        landY = (pos.y + slopeY - slopePos.y) + ((playerRect.size.height * 0.5f) * -flipMod());
                    else
                        landY = (pos.x + slopeY - slopePos.y) + ((playerRect.size.width * 0.5f)  * -flipMod());
                }

                if (m_isSideways)
                    unrotateGameplayObject(obj);
            }

            float yPos = !m_isSideways ? playerPos.y : playerPos.x;

            if ((!m_isUpsideDown && landY < (yPos - 10.0f)) ||
                (m_isUpsideDown  && landY > (yPos + 10.0f))
            ) continue;

            if (m_isPlatformer && !checkingSlope) break;

            // In classic mode, the check runs only for objects 
            // ahead of the player in the travel direction.
            if (!m_isPlatformer) {

                if (!m_isGoingLeft) {
                    CCRect objRect = obj->getObjectRect();

                    float minX = !m_isSideways ? objRect.getMinX() : objRect.getMinY();
                    float x    = !m_isSideways ? playerPos.x : playerPos.y;

                    if (minX <= x) break;
                }
                if (m_isGoingLeft) {
                    CCRect objRect = obj->getObjectRect();

                    float maxX = !m_isSideways ? objRect.getMaxX() : objRect.getMaxY();
                    float x    = !m_isSideways ? playerPos.x : playerPos.y;

                    if (maxX >= x) break;
                }

            }

            // Second loop, test for a hit to find landing spot

            bool hit = false;

            for (int j = 0; j < staticObjects->count(); j++) {
                GameObject* innerObj = (GameObject*)staticObjects->objectAtIndex(j);

                // Skip self
                if (j == i) continue;

                if (!m_isSideways)
                    playerRect.origin.y = landY - (playerRect.size.height * 0.5f);
                else
                    playerRect.origin.x = landY - (playerRect.size.width * 0.5f);

                CCRect objRect = innerObj->getObjectRect();
                
                // Shrink the block's
                if (!checkingSlope) { 
                    if (!m_isSideways) {
                        objRect.size.height -= 4.0f;
                        objRect.origin.y += 2.0f;
                    }
                    else {
                        objRect.size.width -= 4.0f;
                        objRect.origin.x += 2.0f;
                    }
                }

                if (objRect.intersectsRect(playerRect)) {
                    if (checkingSlope) {
                        if (prevLandY != 0.0f) {
                            landY = !m_isUpsideDown ? MIN(landY, prevLandY) : MAX(landY, prevLandY);
                        }
                    }
                    else {
                        landY = prevLandY;
                    }

                    hit = true;
                    prevLandY = landY;
                    break;
                }
            }
            if (!hit) break;
        }

        // If we had to check every object, mark landY as not found
        if (i >= staticObjects->count()) landY = 0.0f;
    }

    // Set landY to the max/min teleport if no block was found
    if (!m_isPlatformer || prevLandY == 0.0f) {
        if (landY == 0.0f) {
            float h = !m_isSideways ? (playerRect.size.height) : (playerRect.size.width);
            landY = m_isUpsideDown ? (minTeleport + h * 0.5f) : (maxTeleport - h * 0.5f);
        }
    }
    else {
        bool prevIsCloser = m_isUpsideDown ? (prevLandY > landY) : (prevLandY < landY);
        if (prevIsCloser || landY == 0.0f) landY = prevLandY;
    }

    // Found both solids and hazards in the travel rect.
    // Check for prevention of the spider teleporting past a 
    // spike to a solid surface.
    if (!onlyFoundDamagingObjects && damagingObjects->count() != 0) {
        GameObject* nearestHazard = (GameObject*)damagingObjects->objectAtIndex(0);
        CCPoint nearestHazardPos = nearestHazard->getRealPosition();

        float nearestHazardY = !m_isSideways ? nearestHazardPos.y : nearestHazardPos.x;

        // If the nearest hazard is closer than landing spot,
        // force landY to become that to prevent teleportation
        // past the spike.
        if ((!m_isUpsideDown && nearestHazardY < landY) ||
            (m_isUpsideDown && nearestHazardY > landY))
        {
            if (!isRetry) {
                spiderTestJumpInternal(true);
                return;
            }

            landY = nearestHazardY;            
        }
    }

    CCPoint landPos = getPosition();
    CCPoint oldPos = landPos;

    if (!m_isSideways)
        landPos.y = landY;
    else
        landPos.x = landY;

    setPosition(landPos);

    flipGravity(!m_isUpsideDown, true);
    setYVelocity(-flipMod(), 36); // velocity becomes +1/-1

    m_isGroundTouchSideValid = false; // TODO: find better rename (particle related I think)
    m_holdingJump = false;

    resetCollisionLog(true);

    if (!m_isSideways)
        m_position.y = landPos.y;
    else
        m_position.x = landPos.x;

    m_lastSpiderFlipTime = m_totalTime;

    playSpiderDashEffect(oldPos, landPos);

    if (notAffectedByDualGrounds && m_gameLayer != NULL) {
        m_gameLayer->checkCameraLimitAfterTeleport(this, 60.0f);
    }
}