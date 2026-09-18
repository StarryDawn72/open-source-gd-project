void PlayerObject::preCollision() {
    bool& m_onGround = m_isOnGround2;
    bool& m_ringJumpingThisTick = m_ringJumpRelated;
    int& m_slopeSlideTimer = m_maybeSlidingTime;
    double& m_slopeForceEndTime = m_maybeSlidingStartTime;
    GameObject*& m_preSlopeObject = m_currentPotentialSlope;
    std::unordered_map<int, GameObject*>& m_preSlopeObjects = m_potentialSlopeMap;

    m_isOnGround4 = m_onGround;
    m_ringJumpingThisTick = false;
    m_wasOnSlope = m_isOnSlope;
    m_isOnSlope = false;

    m_collidedTopMinY = 0.0;
    m_collidedBottomMaxY = 0.0;
    m_collidedLeftMaxX = 0.0;
    m_collidedRightMinX = 0.0;

    if (m_onGround && !m_platformerMovingLeft && !m_platformerMovingRight && m_slopeSlideTimer > 0) {
        m_slopeSlideTimer = 0;
        m_slopeForceEndTime = m_totalTime;
    }

    if (m_unk669)
        m_preSlopeObject = nullptr;
    else
        m_unk669 = true;

    m_preSlopeObjects.clear();

    if (m_preSlopeObject)
        m_preSlopeObjects[m_preSlopeObject->m_uniqueID] = m_preSlopeObject;

    if (m_currentSlope)
        m_preSlopeObjects[m_currentSlope->m_uniqueID] = m_currentSlope;
}