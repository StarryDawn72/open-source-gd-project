void PlayerObject::disablePlayerControls()
{
    m_controlsDisabled = false;
    m_inputsLocked = true;

    releaseButton(PlayerButton::Jump);
    releaseButton(PlayerButton::Left);
    releaseButton(PlayerButton::Right);
    releaseButton(static_cast<PlayerButton>(5));

	m_controlsDisabled = true;
    m_inputsLocked = false;
}