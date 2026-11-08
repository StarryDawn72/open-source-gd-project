void HardStreak::clearAboveXPos(float x) {
    while (m_pointArray->count() > 1) {
        CCPoint point = ((PointNode*)m_pointArray->objectAtIndex(1))->m_point;
        if (point.x <= x)
            break;
        m_pointArray->removeObjectAtIndex(0, true);
    }
}