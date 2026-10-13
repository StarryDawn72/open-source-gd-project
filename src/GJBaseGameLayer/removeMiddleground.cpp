void GJBaseGameLayer::removeMiddleground()
{
    if (m_middleground) {
        m_middleground->removeFromParent();
        m_middleground = nullptr;
    }
}