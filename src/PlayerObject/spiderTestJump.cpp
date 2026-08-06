void PlayerObject::spiderTestJump(bool dynamic)
{
	spiderTestJumpInternal(dynamic);

	if (m_gameLayer)
		gameEventTriggered(static_cast<int>(GJGameEvent::SpiderTeleport), 0);

	if (isInBasicMode()){

		int rotation = 0; // why int robtop, why int

		if (!m_isUpsideDown)
			rotation = m_isSideways ? 270.0f : 0.0f;
		else
			rotation = m_isSideways ? 90.0f : 180.0f;

		setRotation(rotation);
	}
}