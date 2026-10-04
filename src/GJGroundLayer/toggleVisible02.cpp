void GJGroundLayer::toggleVisible02(bool visible)
{
    if (m_showGround2 != visible)
    {
        m_showGround2 = visible;

        if (!m_showGround1)
            visible = false;

        setVisible(visible);
    }
}