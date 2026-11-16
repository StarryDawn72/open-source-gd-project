void GJBaseGameLayer::shakeCamera(float duration, float strength, float interval)
{
    if (duration > 0 && strength > 0 && !m_skipCameraShake) {
        m_gameState.m_lastShakeTime = 0.0;
        m_gameState.m_cameraShakeOffset = CCPointZero;
        m_gameState.m_cameraShakeDuration = duration;
        m_gameState.m_cameraShakeInterval = interval;
        m_staticCameraShake = false;
        m_gameState.m_cameraShakeStrength = MIN(strength, 100.f);
    }
}