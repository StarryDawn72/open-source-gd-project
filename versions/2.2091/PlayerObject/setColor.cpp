void PlayerObject::setColor(const ccColor3B& color)
{
	setColor(color);
	m_iconSprite->setColor(color);
	m_vehicleSprite->setColor(color);
	m_robotSprite->updateColor01(color);
	m_spiderSprite->updateColor01(color);
}