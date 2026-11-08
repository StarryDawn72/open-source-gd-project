void HardStreak::firstSetup()
{
    addPoint(CCPointZero);
    m_currentPoint = ccp(10.0f, 10.0f);
    updateStroke(0.0f);
    visit();
    reset();
}