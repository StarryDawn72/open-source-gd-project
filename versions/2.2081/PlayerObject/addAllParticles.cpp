void PlayerObject::addAllParticles()
{
	m_parentLayer->addChild(m_playerGroundParticles, 39);
	m_parentLayer->addChild(m_ufoClickParticles, 39);
	m_parentLayer->addChild(m_dashParticles, 39);
	m_parentLayer->addChild(m_robotBurstParticles, 39);
	m_parentLayer->addChild(m_trailingParticles, 39);
	m_parentLayer->addChild(m_shipClickParticles, 39);
	m_parentLayer->addChild(m_vehicleGroundParticles, 61);
	m_parentLayer->addChild(m_landParticles0, 61);
	m_parentLayer->addChild(m_landParticles1, 61);
	m_parentLayer->addChild(m_swingBurstParticles1, 39);
	m_parentLayer->addChild(m_swingBurstParticles2, 39);
}