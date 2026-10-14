void GJBaseGameLayer::updateCameraEdge(int direction, int value)
{
    switch (direction) {
        case 1:
            m_gameState.m_cameraEdgeValue0 = value;
            break;
        case 2:
            m_gameState.m_cameraEdgeValue1 = value;
            break;
        case 3:
            m_gameState.m_cameraEdgeValue2 = value;
            break;
        case 4:
            m_gameState.m_cameraEdgeValue3 = value;
            break;
        default:
            return;
    }
}