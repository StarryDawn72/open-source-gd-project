void GJBaseGameLayer::setStartPosObject(StartPosObject* startPos)
{
    if (m_startPosObject != startPos) {
        if (startPos)
            startPos->retain();
        if (m_startPosObject)
            m_startPosObject->release();
        m_startPosObject = startPos;
    }
}