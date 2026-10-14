void GJBaseGameLayer::removeGroundLayer()
{
    if (m_groundLayer) {
        m_groundLayer->removeFromParent();
        m_groundLayer = nullptr;
        m_groundLayer2->removeFromParent();
        m_groundLayer2 = nullptr;
    }
}