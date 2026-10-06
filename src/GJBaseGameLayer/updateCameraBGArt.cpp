#define kMiddlegroundBaseSpeed 0.3f
#define kMiddlegroundBaseScale 1.2f

/*
    Updates the ground, background, and middleground
    parallax based on camera position every frame.
*/
void GJBaseGameLayer::updateCameraBGArt(CCPoint cameraPosition, float zoom)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    bool editorNotPlaying = m_isEditor && !m_started;

    // Background parallax section //

    float lastZoomedScreenH = winSize.height / m_gameState.m_lastCameraZoom;
    float lastZoomedScreenW = winSize.width / m_gameState.m_lastCameraZoom;

    CCPoint screenHalfSize = ccp(winSize.width  / m_gameState.m_cameraZoom * 0.5f,
                                 winSize.height / m_gameState.m_cameraZoom * 0.5f);

    CCPoint screenCenter = cameraPosition + screenHalfSize;

    CCPoint lastScreenHalfSize = ccp(lastZoomedScreenW * 0.5f, lastZoomedScreenH * 0.5f);
    CCPoint lastScreenCenter = m_gameState.m_cameraLastPosition + lastScreenHalfSize;
    CCPoint stepDiff = lastScreenCenter - screenCenter;

    m_gameState.m_cameraStepDiff = stepDiff;

    if (m_skipArtReload) // Unsure about the name
        stepDiff = CCPointZero;

    float flipProgress = m_gameState.m_levelFlipProgress;
    float flipFactor;
    
    // flipFactor is used to make the background art slow down
    // and smoothly scroll back the other way when the level flips from a mirror portal.
    // 1 -> 0 -> -1
    if (flipProgress > 0.5f)
        flipFactor = (flipProgress - 0.5f) * -2.0f;
    else
        flipFactor = 1.0f - (flipProgress * 2.0f);

    CCPoint bgPos = m_background->getPosition();

    CCPoint newBackgroundPos = ccp(bgPos.x + (stepDiff.x * m_gameState.m_backgroundSpeedX * zoom * flipFactor),
                                   bgPos.y + (stepDiff.y * m_gameState.m_backgroundSpeedY * zoom));

    if (m_gameState.m_backgroundWidth != 0.0f) {
        newBackgroundPos.x = fmodf(newBackgroundPos.x, m_gameState.m_backgroundWidth);

        if (newBackgroundPos.x > 0.0f)
            newBackgroundPos.x -= m_gameState.m_backgroundWidth;
    }

    m_background->setPosition(newBackgroundPos);

    // Middleground parallax section //

    if (m_middleground) {
        float prevMgScale = m_middleground->m_groundScale;

        float levelZoomY = m_objectLayer->getScaleY();
        float levelZoomX = m_objectLayer->getScaleX();
        float levelY = m_objectLayer->getPosition().y;

        float mgScale = editorNotPlaying
            ? m_objectLayer->getScaleY()
            : 1.0f - (1.0 - fabsf(levelZoomX)) * kMiddlegroundBaseSpeed;

        float finalMgScale = mgScale * kMiddlegroundBaseScale;
        float deltaMiddlegroundWidth = 0.0f;

        if (m_middleground->m_groundScale != finalMgScale)
            deltaMiddlegroundWidth = m_middleground->scaleGround(finalMgScale);

        float mgStep = (stepDiff.x * m_gameState.m_middlegroundSpeedX * (zoom / finalMgScale) * flipFactor) + deltaMiddlegroundWidth * 0.5;
        float newMiddlegroundY;

        if (prevMgScale == 0.0f)
            prevMgScale = mgScale * kMiddlegroundBaseScale;

        if (editorNotPlaying) {
            newMiddlegroundY = levelY + ((m_middleground->m_ground2Offset + m_gameState.m_middleGroundOffsetY) * finalMgScale);
            bool zoomChanged = m_gameState.m_lastCameraZoom != m_gameState.m_cameraZoom;

            if (zoomChanged)
                mgStep = ((winSize.width / finalMgScale) - (winSize.width / prevMgScale)) * 0.5f;
        }
        else
        {
            float middlegroundOffsetY = m_middleground->m_ground2Offset + m_gameState.m_middleGroundOffsetY;
            float zoomBlend = (1.0f - m_gameState.m_middlegroundSpeedY) + (levelZoomY * m_gameState.m_middlegroundSpeedY);
            float scrollOffsetY = cameraPosition.y * m_gameState.m_middlegroundSpeedY;

            newMiddlegroundY = (middlegroundOffsetY * zoomBlend) - scrollOffsetY;
        }

        m_middleground->setPosition(ccp(0.0f, newMiddlegroundY));

        CCPoint mgPos = m_middleground->m_ground1Sprite->getPosition();
        CCPoint newMiddlegroundPos = ccp(mgPos.x + mgStep, mgPos.y);

        float newX = newMiddlegroundPos.x;
        float textureWidth = m_middleground->m_textureWidth;

        while (newX < -textureWidth)
            newX += textureWidth;

        while (newX > 0.0f)
            newX -= textureWidth;

        newMiddlegroundPos.x = newX;

        if (m_gameState.m_cameraAngle != 0.0f)
            newMiddlegroundPos.x = newX - textureWidth;

        m_middleground->updateGroundPos(newMiddlegroundPos);
    }

    // Ground parallax section //

    float deltaGroundWidth = 0.0f;

    if (m_gameState.m_lastCameraZoom != m_gameState.m_cameraZoom)
    {
        deltaGroundWidth = m_groundLayer->scaleGround(m_gameState.m_cameraZoom);
        m_groundLayer2->scaleGround(m_gameState.m_cameraZoom);
    }

    CCPoint groundPos = m_groundLayer->m_ground1Sprite->getPosition();
    float newGroundX = groundPos.x + (flipFactor * stepDiff.x);
    CCPoint newGroundPos = ccp(newGroundX + (deltaGroundWidth * 0.5f), groundPos.y);
    
    float textureWidth = m_groundLayer->m_textureWidth;

    while (newGroundPos.x < -textureWidth)
        newGroundPos.x += textureWidth;

    while (newGroundPos.x > 0.0f)
        newGroundPos.x -= textureWidth;

    if (m_gameState.m_cameraAngle != 0.0f)
        newGroundPos.x -= textureWidth;

    m_groundLayer->updateGroundPos(newGroundPos);
    m_groundLayer2->updateGroundPos(newGroundPos);

    // Note:
    // m_cameraUnzoomedHeightOffset is always zero.
    // yOff is therefore always zero.
    float yOff = m_cameraUnzoomedHeightOffset * m_gameState.m_cameraZoom * 0.5f;

    CCPoint levelPos = m_objectLayer->getPosition();

    float groundWorldY = m_gameState.m_cameraZoom * 91.0f;
    float dualProgress = m_gameState.m_dualAnimationProgress;
    float winHalfHeight = winSize.height * 0.5f;
    float minGroundY = levelPos.y + groundWorldY;

    float ceilingMaxY = yOff + winSize.height;

    float dualHalfHeight = m_gameState.m_lastModeHeight * 0.5f;

    float groundDualOffset = (((winHalfHeight + (1.0f - dualHalfHeight)) + yOff) * dualProgress) - yOff;
    float ceilingDualOffset = (winHalfHeight + (dualHalfHeight - 1.0f));

    float ceilingDualTravel = ceilingMaxY - ceilingDualOffset;

    float newGroundY = MAX(groundDualOffset, minGroundY);
    float newCeilingY = ceilingMaxY - (ceilingDualTravel * dualProgress);

    m_groundLayer->setPosition(ccp(0.0f, newGroundY));
    m_groundLayer2->setPosition(ccp(0.0f, newCeilingY));

    // Hide the layers when they're off screen
    bool groundOnScreen = !m_hideGround && m_groundLayer->getPosition().y > -yOff;
    m_groundLayer->toggleVisible01(groundOnScreen);

    bool ceilingOnScreen = !m_hideGround && m_groundLayer2->getPosition().y < ceilingMaxY;
    m_groundLayer2->toggleVisible01(ceilingOnScreen);
}