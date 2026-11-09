void PlayerObject::playSpiderDashEffect(CCPoint from, CCPoint to)
{
    if (m_isInPlayLayer && !m_isHidden) {

        from.x += reverseMod() * 7.5f;
        to.x += reverseMod() * 7.5f;

        if (!GM->m_performanceMode) {
            to.x += 6.0f;

            CCCircleWave* ripple1 = CCCircleWave::create((m_playerScale * 10.0f) * 1.3f, 1.0f, 0.15f, false, false);

            ccColor3B color1 = m_swapColors ? m_playerColor1 : m_playerColor2;

            ripple1->m_color.r = color1.r;
            ripple1->m_color.g = color1.g;
            ripple1->m_color.b = color1.b;

            ripple1->setPosition(from);
            m_parentLayer->addChild(ripple1, 0);
            ripple1->m_delegate = PL;

            PL->addCircle(ripple1);
            ripple1->m_opacityMod = 0.42000002f;

            CCCircleWave* ripple2 = CCCircleWave::create((m_playerScale * 20.0f) * 1.3f, 2.0f, 0.25f, false, false);

            ccColor3B color2 = m_swapColors ? m_playerColor1 : m_playerColor2;

            ripple2->m_color.r = color2.r;
            ripple2->m_color.g = color2.g;
            ripple2->m_color.b = color2.b;

            ripple2->setPosition(to);
            m_parentLayer->addChild(ripple2, 0);
            ripple2->m_delegate = PL;

            PL->addCircle(ripple2);
            ripple2->m_opacityMod = 0.84000003f;

            CCCircleWave* ripple3 = CCCircleWave::create(m_playerScale * 10.0f, (m_playerScale * 30.0f) * 1.5f, 0.25f, false, false);

            ccColor3B color3 = m_swapColors ? m_playerColor1 : m_playerColor2;

            ripple3->m_color.r = color3.r;
            ripple3->m_color.g = color3.g;
            ripple3->m_color.b = color3.b;

            ripple3->setPosition(to);
            m_parentLayer->addChild(ripple3, 0);
            ripple3->m_delegate = PL;

            GM->m_playLayer->addCircle(ripple3);
            ripple3->m_circleMode = CircleMode::Outline;
        }

        flashPlayer(0.3f, 0.05f, ccWHITE, ccWHITE);

        m_spiderSprite->stopActionByTag(kTagScaleSpider);
        m_spiderSprite->setScale(0.4f);

        CCEaseElasticOut* elasticScaleEffect = CCEaseElasticOut::create(
            CCScaleTo::create(0.45f, 1.0f),
            0.35f
        );

        elasticScaleEffect->setTag(kTagScaleSpider);
        m_spiderSprite->runAction(elasticScaleEffect);

        if (m_isInPlayLayer) {

            CCSprite* dashSprite = CCSprite::createWithSpriteFrameName("spiderDash_002.png");

            float dashSpriteRotation = !m_isUpsideDown
                ? m_isSideways ? 0.0f : -90.0f
                : m_isSideways ? 180.0f : 90.0f;

            dashSprite->setRotation(dashSpriteRotation);

            PL->m_objectLayer->addChild(dashSprite, 40);

            dashSprite->setBlendFunc({GL_SRC_ALPHA, GL_ONE});

            float fromY = m_isSideways ? from.x : from.y;
            float toY = m_isSideways ? to.x : to.y;
            dashSprite->setScaleX((fabsf(fromY - toY) + 30.f) / dashSprite->getContentSize().width);

            float effectX = from.x;
            float effectY = from.y + ((to.y - from.y) * 0.5f);
            
            if (m_isSideways) {
                effectY = from.y;
                effectX = from.x + ((to.x - from.x) * 0.5f);
            }

            dashSprite->setPosition(ccp(effectX, effectY));
            dashSprite->setColor(m_swapColors ? m_playerColor1 : m_playerColor2);

            CCArray* frames = CCArray::create();

            for (int i = 1; i < 9; i++) {
                CCString* name = CCString::createWithFormat("spiderDash_%03d.png", i);
                frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
            }

            CCAnimate* anim = CCAnimate::create(CCAnimation::createWithSpriteFrames(frames, 0.04f));
            dashSprite->runAction(CCSequence::create(
                anim,
                CCCallFunc::create(dashSprite, callfunc_selector(CCNode::removeMeAndCleanup)),
                NULL
            ));
        }
    }

    if (!m_isHidden && (!m_isSpider || !m_isPlatformer))
        m_playerGroundParticles->resetSystem();
}