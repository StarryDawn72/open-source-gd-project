#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::startDashing(DashRingObject* object)
{
    // Rename incorrect Geode binding names
    bool& m_isInPlayLayer = m_playEffects;

    if (m_isDashing)
        return;

    m_isDashing = true;
    m_lastLandTime = 0;

    stopRotation(false, 3);

    if (m_isPlatformer && isInNormalMode())
        stopPlatformerJumpAnimation();

    if (!m_isDart)
        deactivateStreak(false);

    m_dashFireSprite->setVisible(true);

    float finalDashAngle = m_dashAngle;

    if (!object) {
        m_hasNoEffects = false;
    }
    else {
        m_dashRing = object;
        m_hasNoEffects = object->m_hasNoEffects;
        m_dashStartTime = m_totalTime;

        finalDashAngle = -object->m_startRotationX;
        float ringRot = object->getObjectRotation();

        if (object->isFlipX())
            ringRot += 180.0f;

        if (fabs(object->getRotationX() - object->getRotationY()) > 179.0f)
            ringRot += 180.0f;

        finalDashAngle = fmod(-ringRot, 360.0);
        snapRotation360(finalDashAngle);

        if (!m_isPlatformer)
            limitDashRotation(finalDashAngle);

        CCPoint dashVector = ccpForAngle(CC_DEGREES_TO_RADIANS(finalDashAngle));
        float speedMod = m_isPlatformer ? object->m_dashSpeed * 5.770002f : 1.0f;
        // 5.770002f is the player's global speed multiplier at 1x speed. See updateTimeMod.

        CCPoint dashPos = dashVector * speedMod;

        if (m_isSideways) {
            float y = dashPos.y;
            dashPos.y = dashPos.x;
            dashPos.x = y;
        }

        m_dashX = dashPos.x;
        m_dashY = dashPos.y;

        if (!m_isPlatformer) {
            m_dashY = dashPos.y / fabsf(dashPos.x);
            m_dashX = fabs(m_dashY);
        }
        else if (dashPos.x < 0) {
            doReversePlayer(true);
        }
        else if (dashPos.x > 0) {
            doReversePlayer(false);
        }

        m_dashAngle = finalDashAngle;        
    }

    updateDashArt();
    m_dashFireSprite->stopAllActions();

    // Dash sprite startup animation begins here

    float finalScale = m_dashFireSprite->getScaleX() * 1.1f;

    m_dashFireSprite->setScaleX(0.3f);
    m_dashFireSprite->setScaleY(0.2f);

    CCScaleTo* dashScaleEffect1 = CCScaleTo::create(0.1f, finalScale * 0.9f);
    CCEaseInOut* dashScaleEase1 = CCEaseInOut::create(dashScaleEffect1, 2.0f);

    CCScaleTo* dashScaleEffect2 = CCScaleTo::create(0.1f, finalScale);
    CCEaseInOut* dashScaleEase2 = CCEaseInOut::create(dashScaleEffect2, 2.0f);

    CCSequence* dashScaleSequence = CCSequence::create(dashScaleEase1, dashScaleEase2, NULL);
    m_dashFireSprite->runAction(dashScaleSequence);

    m_dashParticles->resumeSystem();

    ccColor3B dashFireColor = m_switchDashFireColor ? m_playerColor1 : m_playerColor2;

    if (object && m_isInPlayLayer && !m_hasNoEffects) {

        // Play the dash boom effect on the orb if effects are enabled

        CCSprite* dashBoomSprite = CCSprite::createWithSpriteFrameName("playerDash2_boom2_001.png");
        PL->m_objectLayer->addChild(dashBoomSprite, 40);

        dashBoomSprite->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
        dashBoomSprite->setRotation(finalDashAngle * -1);
        dashBoomSprite->setScale(1.2f);
        dashBoomSprite->setPosition(object->getRealPosition());
        dashBoomSprite->setColor(ccc3(255, 255, 255));

        CCArray* frames = CCArray::create();
        for (int i = 1; i <= 9; i++) {
            CCString* frameName = CCString::createWithFormat("playerDash2_boom2_%03d.png", i);
            CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
            frames->addObject(frame);
        }

        CCAnimation* dashBoomAnim = CCAnimation::createWithSpriteFrames(frames, 0.05f);
        CCAnimate* dashBoomAnimate = CCAnimate::create(dashBoomAnim);

        CCCallFunc* removeCall = CCCallFunc::create(dashBoomSprite, callfunc_selector(CCNode::removeMeAndCleanup));
        CCSequence* dashBoomSequence = CCSequence::create(dashBoomAnimate, removeCall, NULL);

        dashBoomSprite->runAction(dashBoomSequence);

        CCDelayTime* fadeOutDelay = CCDelayTime::create(0.2f);
        CCFadeOut* fadeOutAction = CCFadeOut::create(0.3f);
        CCSequence* fadeOutSequence = CCSequence::create(fadeOutDelay, fadeOutAction, NULL);

        dashBoomSprite->runAction(fadeOutSequence);

        int greenDashRingId = 1704;
        
        ccColor3B tint = object->m_objectID == greenDashRingId
            ? ccc3(0, 255, 0)
            : ccc3(255, 0, 255);

        CCTintTo* tintAction = CCTintTo::create(0.3f, tint.r, tint.g, tint.b);
        dashBoomSprite->runAction(tintAction);

        flashPlayer(0.2f, 0.1f, ccc3(255, 255, 255), ccc3(255, 255, 255));

        m_dashFireSprite->setColor(ccc3(255, 255, 255));

        CCDelayTime* fireTintDelay = CCDelayTime::create(0.1f);
        CCTintTo* fireTintAction = CCTintTo::create(
            0.2f,
            dashFireColor.r,
            dashFireColor.g,
            dashFireColor.b
        );
        CCSequence* fireTintSequence = CCSequence::create(fireTintDelay, fireTintAction, NULL);
        m_dashFireSprite->runAction(fireTintSequence);
    }

    m_lastGroundedPos = CCPointZero;

    if (m_gameLayer)
        gameEventTriggered((int)GJGameEvent::DashStart, 0);
}