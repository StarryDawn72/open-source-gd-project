void PlayerObject::updatePlayerScale()
{
	float playerScale = m_vehicleSize;

    m_actionManager->stopInternalAction(6);
    setScaleX(playerScale);
    setScaleY(playerScale);
}