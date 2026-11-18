bool PlayerObject::switchedDirTo(PlayerButton button)
{
    if (!m_inputsLocked) {
        m_holdingButtons[static_cast<int>(PlayerButton::Right)] = button == PlayerButton::Right;
        m_holdingButtons[static_cast<int>(PlayerButton::Left)]  = button == PlayerButton::Left;
    }

    if (!m_controlsDisabled) {
        if (button == PlayerButton::Right) {
            m_holdingRight = true;
            m_leftPressedFirst = false;

            if (m_applySlideBoost && m_isSlidingRight) {
                m_applySlideBoost = false;
                m_slideBoostValue = 0.f;
            }

            if (m_platformerXVelocity >= 0.f)
                return true;
        }
        else { // left
            m_holdingLeft = true;
            m_leftPressedFirst = true;

            if (m_applySlideBoost && !m_isSlidingRight) {
                m_applySlideBoost = false;
                m_slideBoostValue = 0.f;
            }

            if (m_platformerXVelocity <= 0.f)
                return true;
        }

        m_forceLowFriction = false;
        return true;
    }

    return false;
}