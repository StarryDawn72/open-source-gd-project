// @version 2.2081
void PlayerObject::hardFlipGravity()
{
    flipGravity(!m_isUpsideDown, true);
    setYVelocity(-2 * flipMod(), 42);
}