bool PlayerObject::isSafeSpiderFlip(float flipTime)
{
    return m_lastSpiderFlipTime != 0.0 && (m_totalTime - m_lastSpiderFlipTime) < flipTime;
}