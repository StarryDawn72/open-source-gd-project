/*
    No call sites for this function. It's unused.
*/
void PlayerObject::specialGroundHit()
{
    // rename bindings
    bool& m_didSpecialGroundHit = m_maybeSpriteRelated;

    setYVelocity(double(-5 * flipMod()), 47);

    if (!m_isBall && !isFlying())
        stopRotation(false, 21);

    m_didSpecialGroundHit = true;
}