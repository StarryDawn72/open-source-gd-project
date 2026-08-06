void PlayerObject::gameEventTriggered(int gameEvent, int material)
{
	if (m_gameLayer)
		m_gameLayer->gameEventTriggered(static_cast<GJGameEvent>(gameEvent), material, m_uniqueID);
}