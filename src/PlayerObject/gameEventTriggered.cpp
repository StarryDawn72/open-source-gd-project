// @version 2.2081
void PlayerObject::gameEventTriggered(int gameEvent, int material)
{
	if (m_gameLayer)
		m_gameLayer->gameEventTriggered((GJGameEvent)gameEvent, material, m_uniqueID);
}