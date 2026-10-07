bool PlayerObject::releaseButton(PlayerButton button)
{
    if ((int)button == 5)
    {
        releaseButton(PlayerButton::Left);
        releaseButton(PlayerButton::Right);
        return !m_controlsDisabled;
    }

    if (!m_inputsLocked)
        m_holdingButtons[(int)button] = false;

    if (m_controlsDisabled)
        return false;

    if (m_holdingJump)
        placeStreakPoint();

    switch (button)
    {
        case PlayerButton::Jump:
            m_touchedPad = true;
            m_holdingJump = false;
            m_isJumpUnused = false;
            if (m_isDashing)
                stopDashing();
            break;
        case PlayerButton::Left:
            m_holdingLeft = false;
            if (m_platformerXVelocity < 0.0f)
                m_isMoving = false;
            break;
        case PlayerButton::Right:
            m_holdingRight = false;
            if (m_platformerXVelocity > 0.0f)
                m_isMoving = false;
            break;
    }
    return true;
}