void PlayerObject::resetStateVariables() {
    m_noAutoJumpTimer = 0;
    m_allowDartSlideTimer = 0;
    m_flipBlockTimer = 0;
    m_allowHeadHitTimer = 0;
    m_stateOnGround = 0; // TODO: RENAME
    m_stateBoostX = 0; // TODO: RENAME
    m_stateBoostY = 0; // TODO: RENAME
    m_maybeStateForce2 = 0; // TODO: RENAME
    m_stateScale = 0; // TODO: RENAME
    m_forceTimer = 0;
    m_forceVector = CCPointZero;
    m_activeForceIDs.clear();
}