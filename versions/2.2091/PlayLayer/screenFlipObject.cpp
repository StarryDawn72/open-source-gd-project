/*
    Ran on every visible object during a mirror portal transition.
*/
void PlayLayer::screenFlipObject(GameObject* object)
{
    float progress = m_gameState.m_levelFlipProgress;

    if (m_cameraFlip == -1.0f)
        progress = 1.0f - progress;

    CCSize winSize =  CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = object->getPosition();

    object->setPosition(ccp(
        pos.x + (((winSize.width / m_gameState.m_cameraZoom) - ((pos.x - m_gameState.m_cameraPosition.x) + (pos.x - m_gameState.m_cameraPosition.x))) * progress),
        pos.y
    ));

    float absRot = fabsf(object->getRotation());
    bool notSideways = !(absRot == 90.0f || absRot == 270.0f);
    float levelFlipProgress = m_gameState.m_levelFlipProgress;

    bool pastSecondHalf = (m_cameraFlip == 1.0f && levelFlipProgress >= 0.5f) || (m_cameraFlip != 1.0f && levelFlipProgress <= 0.5f);
    
    if (pastSecondHalf) {

        if (notSideways)
            object->setFlipX(!object->m_startFlipX);
        else
            object->setFlipY(!object->m_startFlipY);

        if ((int)absRot % 90)
            object->setRotation(-object->m_startRotationX);

        return;
    }

    if (!m_gameState.m_inSecondHalfOfFlipAnimation)
        return;

    // this check is essentially dead code at this point
    bool pastMidpoint = (m_cameraFlip == 1.0f && levelFlipProgress > 0.5f) || (m_cameraFlip != 1.0f && levelFlipProgress < 0.5f);

    if (!pastMidpoint) {
        int dir = m_cameraFlip == 1.0f ? 1 : -1;

        if (notSideways)
            object->setFlipX(object->m_startFlipX * dir != 0);
        else
            object->setFlipY(object->m_startFlipY * dir != 0);

        if ((int)absRot % 90)
            object->setRotation(dir * object->m_startRotationX);        
    }

}