void PlayerObject::bumpPlayer(float bumpMod, int objectTypeRaw, bool noEffects, GameObject* object) {
    // converting to enum version so we can use enum names
    GameObjectType objectType = (GameObjectType)objectTypeRaw;
    
    if (m_isPlatformer && !m_fixRobotJump)
        m_touchedPad = true;

    if (objectType != GameObjectType::SpiderPad) {
        propellPlayer(bumpMod, noEffects, objectTypeRaw);

        if (m_isPlatformer && !m_isRotating) {
            float scale;
            if (objectType == GameObjectType::RedJumpPad)
                scale = 1.2;
            else
                scale = 1.0;

            animatePlatformerJump(scale);
        }

        if (objectType != GameObjectType::RedJumpPad) {
            m_isAccelerating = false;
            return;
        }

        m_isAccelerating = true;
        m_lastGroundedPos = CCPointZero;
        return;
    }

    if (object != nullptr) {
        // could be the other way around
        if (
            (!m_isSideways && object->isFacingDown() != m_isUpsideDown) ||
            (m_isSideways && object->isFacingLeft() != m_isUpsideDown)
        ) {
            flipGravity(!m_isUpsideDown, true);
        }
    }

    spiderTestJump(false);
    playBumpEffect(44, object);
}