void PlayerObject::updatePlayerScale()
{
    m_actionManager->stopInternalAction(6);
    setScaleX(playerScale);
    setScaleY(playerScale);
}