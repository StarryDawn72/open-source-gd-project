void GJGroundLayer::toggleVisible01(bool visible)
{
    if (m_showGround1 != visible) {
        m_showGround1 = visible;

        if (visible)
            visible = m_showGround2;

        setVisible(visible);
    }
}