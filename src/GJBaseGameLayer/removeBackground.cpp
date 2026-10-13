void GJBaseGameLayer::removeBackground()
{
    if (m_background) {
        m_background->removeFromParent();
        m_background = nullptr;
    }
}