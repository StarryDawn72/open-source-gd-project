#define kTagPlatformerJumpAnimation 13

void PlayerObject::animatePlatformerJump(float scale) {
    if (
        m_holdingLeft || m_holdingRight ||
        m_slopeForceLeft || m_slopeForceRight ||
        !isInNormalMode()
    ) {
        return;
    }

    scale *= 1.35f;

    for (int iconTarget = 0; iconTarget < 2; iconTarget++) {
        int rot = fabsf(getRotation());

        float scaleX1, scaleY1;
        float scaleX2, scaleY2;

        if ((rot >= 46 && rot <= 134) || (rot >= 226 && rot < 315)) {
            scaleX1 = scale;
            scaleY1 = 0.8f;
            scaleX2 = 0.9f;
            scaleY2 = 1.1f;
        } else { // X and Y values flipped
            scaleX1 = 0.8f;
            scaleY1 = scale;
            scaleX2 = 1.1f;
            scaleY2 = 0.9f;
        }

        CCSequence* action = CCSequence::create(
            CCEaseInOut::create(CCScaleTo::create(0.1f  / m_gravityMod, scaleX1, scaleY1), 2.0f),
            CCEaseInOut::create(CCScaleTo::create(0.25f / m_gravityMod, scaleX2, scaleY2), 2.0f),
            CCEaseInOut::create(CCScaleTo::create(0.15f / m_gravityMod, 1.0f, 1.0f), 2.0f),
            NULL
        );

        action->setTag(kTagPlatformerJumpAnimation);

        if (iconTarget == 0)
            m_iconSprite->runAction(action);
        else
            m_iconGlow->runAction(action);
    }
}
