#define kTagActionCompletionPlayerFadeOut 4

void PlayerObject::playCompleteEffect(bool noEffects, bool instant)
{
    if (m_isDart)
        fadeOutStreak2(0.2f);
    stopDashing();

    deactivateParticle();
    m_trailingParticles->stopSystem();
    m_shipClickParticles->stopSystem();
    m_vehicleGroundParticles->stopSystem();
    m_robotBurstParticles->stopSystem();

    if (m_robotFire) {
        m_robotFire->stopAllActions();
        m_robotFire->setVisible(false);
    }

    toggleGhostEffect(GhostType::Disabled);
    disableSwingFire();

    CCLayer* parentLayer = getParent() ? (CCLayer*)getParent() : m_parentLayer;

    if (instant)
        setOpacity(0);
    else {
        auto fade = CCFadeTo::create(0.1f, 0);
        fade->setTag(kTagActionCompletionPlayerFadeOut);
        runAction(fade);
    }

    if (noEffects)
        return;

    auto explodeEffect = CCParticleSystemQuad::create("explodeEffectVortex.plist", false);

    explodeEffect->setPositionType(tCCPositionType::kCCPositionTypeGrouped);
    explodeEffect->setAutoRemoveOnFinish(true);
    m_parentLayer->addChild(explodeEffect, 99);
    explodeEffect->setPosition(getPosition());

    explodeEffect->setStartColor(ccc4FFromccc3B(m_playerColor1));
    explodeEffect->setEndColor(ccc4f(0.0f, 0.0f, 1.0f, 1.0f));
    explodeEffect->setBlendAdditive(true);

    explodeEffect->setStartColorVar(ccc4f(0.0f, 0.0f, 0.0f, 1.0f));
    explodeEffect->setEndColorVar(ccc4f(0.0f, 0.0f, 0.0f, 1.0f));

    // not sure what the idea was here
    explodeEffect->setSpeed(explodeEffect->getSpeed());
    explodeEffect->setLife(explodeEffect->getLife() * 3.0f);
    explodeEffect->setPosVar(explodeEffect->getPosVar() * 1.2f);
    explodeEffect->setStartSize(explodeEffect->getStartSize() * 0.8f);
    explodeEffect->setEndSize(explodeEffect->getEndSize() * 0.4f);

    explodeEffect->resetSystem();

    auto wave1 = CCCircleWave::create(20.0f, 80.0f, 0.72f, false);
    wave1->m_color = m_playerColor1;
    wave1->setPosition(getPosition());
    parentLayer->addChild(wave1, 99);

    auto wave2 = CCCircleWave::create(30.0f, 50.0f, 0.84000003f, false);
    wave2->m_color = m_playerColor2;
    wave2->setPosition(getPosition());
    wave2->m_opacityMod = 0.8f;
    m_parentLayer->addChild(wave2, 1000);

    auto wave3 = CCCircleWave::create(30.0f, 20.0f, 0.96000004f, false);
    wave3->m_color = m_playerColor1;
    wave3->setPosition(getPosition());
    wave3->m_opacityMod = 0.8f;
    m_parentLayer->addChild(wave3, 1000);
}