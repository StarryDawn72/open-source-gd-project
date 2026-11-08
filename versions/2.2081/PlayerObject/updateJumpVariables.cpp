void PlayerObject::updateJumpVariables()
{
    m_holdingJumpReleaseDelayed = m_holdingJump;
    m_canRingJump = m_isJumpUnused;
    m_touchedRing = false;
    m_touchedCustomRing = false;
    m_touchedTeleportRing = false;
    m_maybeTouchedBreakableBlock = false; // TODO: Find better name
}