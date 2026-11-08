void PlayerObject::setOpacity(unsigned char opacity)
{
	GameObject::setOpacity(opacity);
	m_iconSprite->setOpacity(opacity);
	m_iconSpriteSecondary->setOpacity(opacity);
	m_iconSpriteWhitener->setOpacity(opacity);
	m_iconGlow->setOpacity(opacity);
	m_vehicleSprite->setOpacity(opacity);
	m_vehicleSpriteSecondary->setOpacity(opacity);
	m_birdVehicle->setOpacity(opacity);
	m_vehicleSpriteWhitener->setOpacity(opacity);
	m_vehicleGlow->setOpacity(opacity);
	m_robotSprite->setOpacity(opacity);
	m_spiderSprite->setOpacity(opacity);
}