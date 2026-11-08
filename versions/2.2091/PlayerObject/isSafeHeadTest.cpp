bool PlayerObject::isSafeHeadTest()
{
    return isSafeFlip(0.2f) || isSafeMode(0.2f) || m_stateHitHead > 0;
}