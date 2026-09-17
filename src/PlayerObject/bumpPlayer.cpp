void PlayerObject::bumpPlayer(float bumpMod, int objectType, bool noEffects, GameObject* object) {

    GameObjectType type = (GameObjectType)objectType;

    // Rename incorrect bindings
    bool& m_isVelocityUncapped = m_isAccelerating;
    
    if (m_isPlatformer || !m_fixRobotJump)
        m_touchedPad = true; // TODO: name is probably incorrect, might need a rename

    if (type == GameObjectType::SpiderPad) {
        if (object) {
            if (
                (!m_isSideways && object->isFacingDown() != m_isUpsideDown) ||
                (m_isSideways && object->isFacingLeft() != m_isUpsideDown)
            ) {
                flipGravity(!m_isUpsideDown, true);
            }
        }

        spiderTestJump(false);
        playBumpEffect((int)GameObjectType::SpiderPad, object);
        return;
    }

    propellPlayer(bumpMod, noEffects, objectType);

    if (m_isPlatformer && !m_isRotating) {
        float scale = (type == GameObjectType::RedJumpPad)
                    ? 1.2f
                    : 1.0f;

        animatePlatformerJump(scale);
    }

    if (type == GameObjectType::RedJumpPad) {
        m_isVelocityUncapped = true;
        m_lastGroundedPos = CCPointZero;
    }
    else
        m_isVelocityUncapped = false;
}
