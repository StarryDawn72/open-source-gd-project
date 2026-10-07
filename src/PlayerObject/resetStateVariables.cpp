void PlayerObject::resetStateVariables()
{
    m_noAutoJumpTimer = 0;
    m_forceVector = CCPointZero;
    m_activeForceIDs.clear();
}