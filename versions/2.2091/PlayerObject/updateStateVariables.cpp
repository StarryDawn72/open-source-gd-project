void PlayerObject::updateStateVariables() {
    m_noAutoJumpTimer--;
    m_allowDartSlideTimer--;
    m_flipBlockTimer--;
    m_allowHeadHitTimer--;
    m_groundHitTimer--;
    m_boostXTimer--;
    m_boostYTimer--;
    m_maybeStateForce2--; // TODO: RENAME
    m_scaleChangeTimer--;
    m_forceTimer--;
    m_forceVector = CCPointZero;
    m_activeForceIDs.clear();
}