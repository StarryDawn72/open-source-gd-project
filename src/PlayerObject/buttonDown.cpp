bool PlayerObject::buttonDown(PlayerButton button)
{
    return button == PlayerButton::Jump && m_holdingJump;
}