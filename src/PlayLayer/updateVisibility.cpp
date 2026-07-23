/*
	====== PlayLayer::updateVisibility ======
	
	This function iterates through every object that
	is currently visible on the player's screen. It is
	responsable for triggering enter effects, audio scale,
	color updates, and the mirror portal transition animation.
	
*/
float s_cameraRight = 0.0f;

void PlayLayer::updateVisibility(float dt)
{
	// File-scoped/static variable. Only used in PlayLayer::applyCustomEnterEffect
    s_cameraRight = m_gameState.m_cameraPosition2.x + m_cameraWidth;

    preUpdateVisibility(dt);
    m_effectManager->processColors();

    ccColor3B player1Color = m_effectManager->activeColorForIndex(1005);
    m_effectManager->calculateLightBGColor(player1Color);

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    ccColor3B backgroundColor = m_background->getColor();
    ccColor3B brightenedBGColor = GameToolbox::transformColor(backgroundColor, ccHSVValue(0.0f, -0.3f, 0.4f, true, true));
    ccColor3B lightBGChannelColor = m_effectManager->activeColorForIndex(1007);
    ccColor3B bgChannelColor = m_effectManager->activeColorForIndex(1000);

    m_lightBGColor = GameToolbox::transformColor(bgChannelColor, ccHSVValue(0.0f, -0.2f, 0.2f, true, true));

    std::fill(m_keyPulses.m_bits.begin(), m_keyPulses.m_bits.end(), 0u);

    float cameraFollowThreshold = (winSize.width / 2) -75.0f;
    float screenRight = CCDirector::sharedDirector()->getScreenRight();
    float invisibleBlockRightFadeWidth = (screenRight - (cameraFollowThreshold + 110.0)) - 90.0;

	ccColor3B invisibleBlockTint;

    if ((bgChannelColor.r + bgChannelColor.g + bgChannelColor.b) >= 150.0f )
        invisibleBlockTint = ccc3(255, 255, 255);
	else
		invisibleBlockTint = lightBGChannelColor;

	
	float currentAudioScale = m_skipAudioStep
		? FMODAudioEngine::sharedEngine()->getMeteringValue()
		: m_audioEffectsLayer->m_audioScale;
		
	if ((m_isPracticeMode && !m_practiceMusicSync) || m_isSilent) {
		currentAudioScale = 0.5f;
	}

    m_player1->m_audioScale = currentAudioScale;
	m_player2->m_audioScale = currentAudioScale;

	bool flipping = isFlipping();

	// Loop through all of the objects visible on screen
	for (int i = 0; i < m_activeObjectsCount; i++) {
		GameObject* obj = m_activeObjects[i];

		if (obj->m_mainColorKeyIndex <= 0) {

			// Unused function parameter
			obj->updateMainColor(ccc3(0, 0, 0));
			obj->updateSecondaryColor(ccc3(0, 0, 0));
		}
		else {

			bool unknown1 = ((1 << (obj->m_mainColorKeyIndex & 0x1F)) & m_keyPulses.m_bits[obj->m_mainColorKeyIndex >> 5]) == 0;
			if (unknown1) {

				m_keyColors[obj->m_mainColorKeyIndex] = obj->colorForMode(obj->m_activeMainColorID, true);
				m_keyOpacities[obj->m_mainColorKeyIndex] = obj->opacityModForMode(obj->m_activeMainColorID, true);
				m_keyPulses.m_bits[obj->m_mainColorKeyIndex / 32] |= (1u << (obj->m_mainColorKeyIndex % 32));
			}

			obj->updateMainColor(m_keyColors[obj->m_mainColorKeyIndex]);
			obj->m_baseColor->m_opacity = m_keyOpacities[obj->m_mainColorKeyIndex];

			if (obj->hasSecondaryColor())
			{
				bool unknown2 = ((1 << (obj->m_detailColorKeyIndex & 0x1F)) & m_keyPulses.m_bits[obj->m_detailColorKeyIndex >> 5]) == 0;
				if (unknown2) {

					m_keyColors[obj->m_detailColorKeyIndex] = obj->colorForMode(obj->m_activeDetailColorID, false);
					m_keyOpacities[obj->m_detailColorKeyIndex] = obj->opacityModForMode(obj->m_activeDetailColorID, false);
					m_keyPulses.m_bits[obj->m_detailColorKeyIndex / 32] |= (1u << (obj->m_detailColorKeyIndex % 32));
				}
				obj->updateSecondaryColor(m_keyColors[obj->m_detailColorKeyIndex]);
				obj->m_detailColor->m_opacity = m_keyOpacities[obj->m_detailColorKeyIndex];
			}
		}

		if (obj->m_isActivated && m_blendingColors.size() != 0)
		{
			if (
				m_blendingColors.count(obj->m_activeMainColorID) ||
				( obj->hasSecondaryColor() && m_blendingColors.count(obj->m_activeDetailColorID) )
			) {

				obj->addMainSpriteToParent(false);
				obj->addColorSpriteToParent(false);
			}
		}

		obj->activateObject();
		m_enterEffectPosition = obj->getRealPosition();

		float screenCenterX = m_gameState.m_cameraPosition2.x + m_halfCameraWidth;
		bool isRight = false;
		int finalEnterType = m_gameState.m_exitChannelMap[obj->m_enterChannel];
		int objectEnterType = obj->m_exitType;

		if (
			obj->m_enterType != -1 ||
			(obj->m_exitType == -1 && m_enterEffectPosition.x > screenCenterX)
		) {
			isRight = true;
			finalEnterType = m_gameState.m_enterChannelMap[obj->m_enterChannel];
			objectEnterType = obj->m_enterType;
		}


		if ( obj->m_isUIObject ) {
			objectEnterType = -14;
			finalEnterType = -14;
		}

		// Rename bindings
		bool obj_m_isAnimatedGameObject = obj->m_unk367;
		bool obj_m_isEndPortal = obj->m_unk3F8;

		if (obj->getHasSyncedAnimation())
			static_cast<AnimatedGameObject*>(obj)->updateSyncedAnimation(-1, m_gameState.m_totalTime);

		// Update spinning objects such as saws
		if (obj->getHasRotateAction())
			static_cast<EnhancedGameObject*>(obj)->updateRotateAction(dt);

		if (obj_m_isAnimatedGameObject)
            static_cast<AnimatedGameObject*>(obj)->updateChildSpriteColor(brightenedBGColor);

		// Update the bobbing effect on collectible items	
        if (obj->getType() == GameObjectType::Collectible)
            static_cast<EffectGameObject*>(obj)->updateInteractiveHover(m_hoverNode->getPosition().y);

		int breakableBricksID = 143;
        if (obj->m_objectID == breakableBricksID)
            obj->setGlowColor(m_lightBGColor);

		if (obj_m_isEndPortal)
			continue;
		
		// Update pulsing objects
		if (obj->m_usesAudioScale && !obj->m_hasNoAudioScale)
		{
			if (obj->m_customAudioScale)
				obj->setRScale(obj->m_minAudioScale + ((currentAudioScale - 0.1f) * (obj->m_maxAudioScale - obj->m_minAudioScale)));
			else
				obj->setRScale(currentAudioScale);
		}

		if (obj->m_customGlowColor)
		{
			if (obj->m_glowColorIsLBG)
				obj->setGlowColor(lightBGChannelColor);
			else
				obj->setGlowColor(m_lightBGColor);
		}

		
		if (obj->m_isInvisibleBlock)
		{
			// Update the fading block

			if ( m_player1->m_isDead ) {

				// Immediately unhide all invisible blocks on death
				// to show where the player died
				obj->setGlowColor(m_lightBGColor);
				obj->setOpacity(255);
				obj->setGlowOpacity(255);
			}
			else {
				updateInvisibleBlock(
					obj,
					cameraFollowThreshold + 110.0f,
					cameraFollowThreshold,
					invisibleBlockRightFadeWidth,
					cameraFollowThreshold - 30.0f,
					invisibleBlockTint
				);
			}

			if (finalEnterType != -15 || obj->ignoreEnter())
				applyEnterEffect(obj, finalEnterType, isRight);
			else
				applyCustomEnterEffect(obj, isRight);

		}
		else if (obj->ignoreFade() || finalEnterType == -14) {
			obj->setOpacity(255);
				
			if (finalEnterType != -15 || obj->ignoreEnter())
				applyEnterEffect(obj, finalEnterType, isRight);
			else
				applyCustomEnterEffect(obj, isRight);
		}
		else if ( 
			obj->m_intrinsicDontFade
			&& (!obj->m_isSolidColorBlock || !obj->m_baseOrDetailBlending)
			&& (objectEnterType + 2) <= 1
			&& finalEnterType == -2 )
		{
			obj->setOpacity(255);
			applyEnterEffect(obj, finalEnterType, isRight);
		}
		else if (finalEnterType != -15){
			// Update objects fading in and out of the screen
			float fadeX = 0.0f;
			float fadeWidth = 70.0f;

			if (isRight)
				fadeX = m_enterEffectPosition.x - obj->m_fadeMargin;
			else
				fadeX = m_enterEffectPosition.x + obj->m_fadeMargin;

			CCPoint fadePos = ccp(fadeX, fadeWidth);
			
			// Last parameter unused, despite the name in the bindings
			float newOpacity = getRelativeModNew(fadePos, 0.0f, 0.0f, isRight, false) * 255.0f;
			obj->setOpacity(newOpacity);

			applyEnterEffect(obj, finalEnterType, isRight);
		}
		else if (obj->ignoreEnter())
			applyEnterEffect(obj, finalEnterType, isRight);
		else
			applyCustomEnterEffect(obj, isRight);	


		// Animate mirror portal flip animation
		if (flipping) {			
			screenFlipObject(obj);
		}
		else if (m_resetActiveObjects) {
			obj->setFlipX(obj->m_startFlipX);
			obj->setFlipY(obj->m_startFlipY);
			obj->setRotation(obj->m_startRotationX);
			obj->setPosition(obj->getPosition());
		}
    }

	updateEnterEffects(dt);
	processAreaVisualActions(dt);
	updateParticles(dt);
	m_resetActiveObjects = false;
	m_blendingColors.clear();

	// Draw hitboxes
	if (shouldDebugDraw())
		updateDebugDraw();
}