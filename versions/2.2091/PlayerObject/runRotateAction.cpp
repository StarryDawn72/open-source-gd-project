void PlayerObject::runRotateAction(bool ground, int unknown)
{
    if (!m_isLocked && !m_isDashing)
    {
        stopRotation(ground, 22);
        if (m_isBall)
            runBallRotation(1.0f);
        else
            runNormalRotation();
    }
}