void PlayerObject::setSecondColor(const ccColor3B& color)
{
	m_iconSpriteSecondary->setColor(color);
	m_vehicleSpriteSecondary->setColor(color);
	m_robotSprite->updateColor02(color);
	m_spiderSprite->updateColor02(color);
}