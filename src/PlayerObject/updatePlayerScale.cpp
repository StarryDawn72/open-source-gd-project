// @version 2.2081
void PlayerObject::updatePlayerScale()
{
    m_actionManager->stopInternalAction(6);
    setScaleX(playerScale);
    setScaleY(playerScale);
}