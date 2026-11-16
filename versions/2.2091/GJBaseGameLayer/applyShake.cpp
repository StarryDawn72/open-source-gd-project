/*
    Shake offset applied to the camera position every frame
    at the end of GJBaseGameLayer::updateCamera.
*/
void GJBaseGameLayer::applyShake(CCPoint& point)
{
    if (m_gameState.m_lastShakeTime < 0 || m_gameState.m_cameraShakeInterval <= 0 || m_gameState.m_totalTime - m_gameState.m_lastShakeTime > m_gameState.m_cameraShakeInterval) {
        m_gameState.m_lastShakeTime = m_gameState.m_totalTime;

        float x = 0;
        float y = 0;

        if (m_staticCameraShake) {
            // each axis is exactly +1 or -1
            x = CCRANDOM_0_1() > 0.5f ? 1.f : -1.f;
            y = CCRANDOM_0_1() > 0.5f ? 1.f : -1.f;
        }
        else {
            // each axis is a random number in the [-1, 1] range
            x = CCRANDOM_MINUS1_1();
            y = CCRANDOM_MINUS1_1();
        }
        
        float strength = m_gameState.m_cameraShakeStrength;
        m_gameState.m_cameraShakeOffset.x = x * strength;
        m_gameState.m_cameraShakeOffset.y = y * strength;
    }
    
    point.x += m_gameState.m_cameraShakeOffset.x;
    point.y += m_gameState.m_cameraShakeOffset.y;
}