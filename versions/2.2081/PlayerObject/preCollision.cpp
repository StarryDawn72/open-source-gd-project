void PlayerObject::preCollision() 
{
    m_wasOnGround = m_onGround;
    m_ringJumpingThisTick = false;
    m_wasOnSlope = m_isOnSlope;
    m_isOnSlope = false;

    m_collidedTopMinY = 0.0;
    m_collidedBottomMaxY = 0.0;
    m_collidedLeftMaxX = 0.0;
    m_collidedRightMinX = 0.0;

    if (m_onGround && !m_slopeForceLeft && !m_slopeForceRight && m_slopeSlideTimer > 0) {
        m_slopeSlideTimer = 0;
        m_slopeForceEndTime = m_totalTime;
    }

    if (m_shouldDisconnectSlope)
        m_preSlopeObject = nullptr;
    else
        m_shouldDisconnectSlope = true;

    m_preSlopeObjects.clear();

    if (m_preSlopeObject)
        m_preSlopeObjects[m_preSlopeObject->m_uniqueID] = m_preSlopeObject;

    if (m_currentSlope)
        m_preSlopeObjects[m_currentSlope->m_uniqueID] = m_currentSlope;
}
