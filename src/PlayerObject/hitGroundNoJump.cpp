void PlayerObject::hitGroundNoJump(GameObject *object, bool notFlipped)
{
	bool& m_onGround = m_isOnGround2;
	bool& m_canJump = m_isOnGround;
	bool noParticle = notFlipped; // Incorrectly named parameter in geode bindings

    bool prevCanJump = m_canJump;
    bool prevOnGround = m_onGround;
    double prevLastLandTime = m_lastLandTime;

    hitGround(nullptr, noParticle);

    m_lastLandTime = prevLastLandTime;
    m_onGround = prevOnGround;
    m_canJump = prevCanJump;
}