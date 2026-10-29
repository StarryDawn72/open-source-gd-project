// @version 2.2081
void PlayerObject::rotateGameplayOnly(bool sideways)
{
    m_isSideways = sideways;
    updatePlayerArt();
}