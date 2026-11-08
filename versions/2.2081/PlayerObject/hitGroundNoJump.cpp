void PlayerObject::hitGroundNoJump(GameObject *object, bool noParticle)
{
    bool prevCanJump = m_canJump;
    bool prevOnGround = m_onGround;
    double prevLastLandTime = m_lastLandTime;

    hitGround(nullptr, noParticle);

    m_lastLandTime = prevLastLandTime;
    m_onGround = prevOnGround;
    m_canJump = prevCanJump;
}