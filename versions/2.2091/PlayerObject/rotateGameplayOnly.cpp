void PlayerObject::rotateGameplayOnly(bool sideways)
{
    m_isSideways = sideways;
    updatePlayerArt();
}