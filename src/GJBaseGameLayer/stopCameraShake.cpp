void GJBaseGameLayer::stopCameraShake()
{
    m_gameState.m_cameraShakeEnabled = false;
    m_gameState.m_cameraShakeFactor  = 0.0f;
}