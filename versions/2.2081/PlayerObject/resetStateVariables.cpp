void PlayerObject::resetStateVariables() {
    m_noAutoJumpTimer = 0;
    m_allowDartSlideTimer = 0;
    m_flipBlockTimer = 0;
    m_allowHeadHitTimer = 0;
    m_groundHitTimer = 0;
    m_boostXTimer = 0;
    m_boostYTimer = 0;
    m_maybeStateForce2 = 0; // TODO: RENAME
    m_scaleChangeTimer = 0;
    m_forceTimer = 0;
    m_forceVector = CCPointZero;
    m_activeForceIDs.clear();
}