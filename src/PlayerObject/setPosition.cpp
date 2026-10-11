/*
    Since many of the particles, streak and trail effects are put
    as a child of the level node rather than the player node. It
    means that these effects need to have their position updated
    to follow the player every time the player changes position.
    This is what this function does.

    Additionally, it sets the position of many effects like ground particles
    depending on whether the player is upside down, going sideways or
    is on a slope.
*/
void PlayerObject::setPosition(const CCPoint& position)
{
    m_isObjectRectDirty = true;
    m_isOrientedBoxDirty = true;
    GameObject::setPosition(position);

    CCPoint trailingParticlesPos;

    if (m_isSwing)
        trailingParticlesPos = ccp(m_playerScale * -10.0f, 0.0f);
    else {
        CCPoint offset;
        if (m_isPlatformer && m_isShip)
            offset = ccp(m_playerScale * -10.0f, -18.0f);
        else if (m_isBird)
            offset = ccp(0.0f, -3.0f);
        else
            offset = ccp(m_playerScale * -12.0f, -4.0f);
        trailingParticlesPos = m_vehicleSprite->getPosition() + offset;
    }

    CCPoint trailingParticlesWorldPos = m_mainLayer->convertToWorldSpace(trailingParticlesPos);
    if (m_trailingParticles->getParent()) {
        CCPoint pos = m_trailingParticles->getParent()->convertToNodeSpace(trailingParticlesWorldPos);
        m_trailingParticles->setPosition(pos);
    }

    m_shipClickParticles->setPosition(m_trailingParticles->getPosition());
    m_ufoClickParticles->setPosition(m_trailingParticles->getPosition());
    m_dashParticles->setPosition(m_trailingParticles->getPosition());

    CCSpritePart* footSprite = m_robotSprite->m_footSprite;

    const CCSize& footSpriteSize = footSprite->getContentSize();
    CCPoint robotFireWorldPos = footSprite->convertToWorldSpace(ccp(footSpriteSize.width * 0.5f, 2.5f));
    CCPoint robotFirePos = m_robotFire->getParent()->convertToNodeSpace(robotFireWorldPos);

    m_robotFire->setPosition(robotFirePos);
    m_robotFire->setRotation(footSprite->getRotation() * m_robotSprite->m_paSprite->getScaleX() + m_robotSprite->m_paSprite->getRotation());

    if (m_robotBurstParticles->getParent()) {
        CCPoint worldPos = m_robotFire->getParent()->convertToWorldSpace(m_robotFire->getPosition());
        m_robotBurstParticles->setPosition(m_robotBurstParticles->getParent()->convertToNodeSpace(worldPos));
    }

    if (m_swingBurstParticles1->getParent()) {
        CCPoint worldPos = m_swingFireBottom->getParent()->convertToWorldSpace(m_swingFireBottom->getPosition());
        m_swingBurstParticles1->setPosition(m_swingBurstParticles1->getParent()->convertToNodeSpace(worldPos));
    }

    if (m_swingBurstParticles2->getParent()) {
        CCPoint worldPos = m_swingFireTop->getParent()->convertToWorldSpace(m_swingFireTop->getPosition());
        m_swingBurstParticles2->setPosition(m_swingBurstParticles2->getParent()->convertToNodeSpace(worldPos));
    }

    int modY = m_isSwing ? 1 : flipMod();
    modY = m_isGroundTouchSideValid ? modY : -modY;

    CCPoint groundParticlesOffset = m_isRobot ? ccp(0.0f, -2.0f) : ccp(0.0f, 0.0f);

    CCPoint groundParticlesPos = ccp(
        (groundParticlesOffset.x - 10.0f) * m_playerScale * (float)reverseMod(),
        (groundParticlesOffset.y - 13.0f) * (float)modY * m_playerScale
    );

    if (m_isOnSlope) {
        // variable names may not be the greatest
        float playerWidth = m_playerScale * m_height;
        float playerHeight = m_playerScale * 20.0f;
        float slopeDistance = sqrtf(playerWidth * playerWidth + playerHeight * playerHeight) * 0.5f;

        float slopeUphill = m_isSlopeUphillRelative ? 1.0f : -1.0f;

        float slopeAngle = slopeUphill == -1.0f ? -m_slopeAngleRadians : m_slopeAngleRadians;

        float playerAspectAngle = atanf(playerWidth / playerHeight);

        bool isSlopeLeft = m_isGoingLeft;
        if (m_isSlopeUphillRelative) isSlopeLeft = !isSlopeLeft;
        if (m_isUpsideDown) isSlopeLeft = !isSlopeLeft;

        if (isSlopeLeft)
            slopeAngle += playerAspectAngle * slopeUphill;
        else
            slopeAngle -= playerAspectAngle * slopeUphill;

        CCPoint particlesPos = ccp(
            slopeDistance * cosf(slopeAngle) * reverseMod(),
            slopeDistance * sinf(slopeAngle) * reverseMod()
        );

        if (m_isSideways)
            CC_SWAP(particlesPos.x, particlesPos.y, float);

        m_playerGroundParticles->setPosition(position - particlesPos);
    } else if (m_onGround) {
        if (m_isSideways)
            CC_SWAP(groundParticlesPos.x, groundParticlesPos.y, float);
        m_playerGroundParticles->setPosition(position + groundParticlesPos);
    }

    if (m_hasHitGroundAfterGravityChange) {
        CCPoint vehicleParticlesPos = ccp(
            m_playerScale * reverseMod(),
            m_playerScale * -15.0f * flipMod()
        );

        if (m_isSideways)
            CC_SWAP(vehicleParticlesPos.x, vehicleParticlesPos.y, float);

        m_vehicleGroundParticles->setPosition(position + vehicleParticlesPos);
        m_vehicleGroundParticles->setAngle(m_isUpsideDown ? 290.0f : 110.0f);
        m_vehicleGroundParticles->setGravity(ccp(-350.0f, -300 * flipMod()));
        m_vehicleGroundParticles->setRotation(m_isSideways ? 90.0f : 0.0f);
    }

    if (m_isShip) {
        if (m_isPlatformer) {
            CCPoint worldPos = m_mainLayer->convertToWorldSpace(ccp(m_playerScale * -10.0f, m_playerScale * -12.0f));
            m_regularTrail->setPosition(m_regularTrail->getParent()->convertToNodeSpace(worldPos));
        } else {
            CCPoint offset = ccp(4 * reverseMod(), 0.0f);
            if (m_isSideways)
                CC_SWAP(offset.x, offset.y, float);

            m_regularTrail->setPosition(m_trailingParticles->getPosition() + offset);

            if (m_shipStreak) {
                CCPoint offset = offsetForStreak(m_shipStreakType, m_playerSpeed);

                CCPoint pos = m_vehicleSprite->getPosition() + ccp(offset.x * (float)reverseMod(), offset.y);

                CCPoint worldPos = m_mainLayer->convertToWorldSpace(pos);
                m_shipStreak->setPosition(m_regularTrail->getParent()->convertToNodeSpace(worldPos));
            }
        }
    } else if (m_isBird) {
        if (m_regularTrail->getParent()) {
            CCPoint pos = m_vehicleSprite->getPosition() + ccp(0.0f, 0.0f);

            CCPoint worldPos = m_mainLayer->convertToWorldSpace(pos);
            m_regularTrail->setPosition(m_regularTrail->getParent()->convertToNodeSpace(worldPos));
        }
    } else if (m_isSwing) {
        m_regularTrail->setPosition(m_trailingParticles->getPosition());
    } else {
        CCPoint offset = ccp(m_playerScale * -2.0f * reverseMod(), 0.0f);
        if (m_isSideways)
            CC_SWAP(offset.x, offset.y, float);

        m_regularTrail->setPosition(getPosition() + offset);
    }

    if (m_fadeOutStreak && m_isDart)
        m_waveTrail->m_currentPoint = getPosition();

    m_waveTrail->setPosition(getPosition());
}