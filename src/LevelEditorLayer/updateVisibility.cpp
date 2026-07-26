#define GM GameManager::sharedState()
/*
	
	Per frame object visibility pass exclusive to the editor.
	
*/
void LevelEditorLayer::updateVisibility(float dt)
{
    forceShowSelectedObjects(true);
    preUpdateVisibility(dt);
    forceShowSelectedObjects(false);

    bool isPlaytesting = m_playbackMode == PlaybackMode::Playing;

    ccColor3B player1ChannelColor = m_effectManager->activeColorForIndex(1005);
    m_effectManager->calculateLightBGColor(player1ChannelColor);

    ccColor3B backgroundColor = m_background->getColor();
    ccColor3B brightenedBGColor = GameToolbox::transformColor(backgroundColor, ccHSVValue(0.0f, -0.3f, 0.4f, true, true));

    bool gvHideInvisible = GM->getGameVariable("0121"); // "Hide invisible" editor option

	for (int i = 0; i < m_activeObjectsCount; i++) {
		GameObject* obj = m_activeObjects[i];

        if (m_playbackMode == PlaybackMode::Not) {

            obj->updateStartPos();
            obj->setPosition(obj->getRealPosition());
        }

        if (obj->m_isActivated) {

			bool addSpritesToParent = false;
			bool reorder = false;

			if (m_updateColorSprites || obj->m_updateParents) {
				reorder = true;
				addSpritesToParent = true;
			} else {
				int objMainColorMode = obj->getMainColorMode();
				if (m_blendingColors2[objMainColorMode]) {
					addSpritesToParent = true; // reorder stays false
				} else if (obj->hasSecondaryColor()) {
					int secondaryColorMode = obj->getSecondaryColorMode();
					if (m_blendingColors2[secondaryColorMode])
						addSpritesToParent = true; // reorder stays false
				}
			}

			if (addSpritesToParent) {
				obj->addMainSpriteToParent(reorder);
				obj->addColorSpriteToParent(reorder);
				obj->m_updateParents = false;
			}
        }

        obj->activateObject();

        if (
			m_previewAnimations && obj->getHasSyncedAnimation() // 2065 = custom particle object
          	|| m_previewParticles && obj->m_objectID == 2065 && obj->getHasSyncedAnimation() )
        {
            static_cast<EffectGameObject*>(obj)->updateSyncedAnimation(m_gameState.m_totalTime, -1);
        }

        if (m_previewAnimations && obj->getHasRotateAction())
            static_cast<EnhancedGameObject*>(obj)->updateRotateAction(dt);

        if (m_playbackMode == PlaybackMode::Not
			&& obj->getHasSyncedAnimation()
			&& static_cast<EnhancedGameObject*>(obj)->m_animateOnTrigger )
		{
			static_cast<EnhancedGameObject*>(obj)->previewAnimateOnTrigger();
		}

        if (obj->getType() == GameObjectType::Collectible) {

			float offset = isPlaytesting ? m_hoverNode->getPosition().y : 0.0f;
            static_cast<EffectGameObject*>(obj)->updateInteractiveHover(offset);
        }

		float editorOpacity = 0.0f;

        if (isPlaytesting || validGroup(obj, false))
            editorOpacity = 255.0f;
        else
            editorOpacity = 50.0f;
		
        if (gvHideInvisible && obj->m_isHide && !obj->m_isSelected)
            editorOpacity = 0.0f;
                                 // keyframe point object
        else if (obj->m_objectID == 3032 && m_playbackMode == PlaybackMode::Playing)
            editorOpacity = 50.0f;

        if (!m_previewMode && obj->hasSecondaryColor()) {

            obj->m_detailColor->m_opacity = editorOpacity * 0.7f;
            if (obj->m_unk367)
                static_cast<AnimatedGameObject*>(obj)->updateChildSpriteColor(ccc3(255, 255, 255));
        }

        if (!m_previewMode || obj->m_isSelected)
            obj->getMainColor()->m_opacity = 1.0f;

        else {
            GJSpriteColor* objMainColor = obj->getMainColor();
            int objMainColorMode = obj->getMainColorMode();
            objMainColor->m_opacity = m_effectManager->activeOpacityForIndex(objMainColorMode);

            if (obj->hasSecondaryColor()) {

                GJSpriteColor* objSecondaryColor = obj->getSecondaryColor();
                int objSecondaryColorMode = obj->getSecondaryColorMode();
                objSecondaryColor->m_opacity = m_effectManager->activeOpacityForIndex(objSecondaryColorMode);
            }

			ccColor3B activeMainColor = ccc3(255, 255, 255); // what

            activeMainColor = m_effectManager->activeColorForIndex(objMainColorMode);

			if (obj->m_groupCount > 0) {
				for (int j = 0; j < obj->m_groupCount; j++) {
					int groupID = obj->getGroupID(j);
                    activeMainColor = m_effectManager->colorForGroupID(groupID, activeMainColor, !obj->m_customSpriteColor);
				}				
			}

            if ( obj->m_baseColor->m_hsv.h != 0.0f
              || obj->m_baseColor->m_hsv.s != 1.0f
              || obj->m_baseColor->m_hsv.v != 1.0f
              || obj->m_baseColor->m_hsv.absoluteSaturation )
            {
                activeMainColor = m_effectManager->colorForEffect(activeMainColor, obj->m_baseColor->m_hsv);
			}

            obj->updateMainColor(activeMainColor);

			float baseColorOpacity = m_effectManager->activeOpacityForIndex(objMainColorMode);

            if (objMainColorMode <= 0 )
                baseColorOpacity = 1.0;

            if ( obj->m_groupCount > 0 ) {
                for ( int j = 0; j < obj->m_groupCount; j++ ) {
                    baseColorOpacity *= m_effectManager->opacityModForGroup(obj->getGroupID(j));
                }
            }

            obj->m_baseColor->m_opacity = baseColorOpacity;

            if (obj->hasSecondaryColor()) {

                int secondaryColorMode = obj->getSecondaryColorMode();
				ccColor3B secondaryColor = ccc3(255, 255, 255);

                if (secondaryColorMode == 1012) // Lighter
                {
                    ccHSVValue hsv = ccHSVValue(0.0f, 0.65f, 0.15f, false, true);
                    secondaryColor = m_effectManager->colorForEffect(activeMainColor, hsv);// split name
                }
                else
                {
                    if (secondaryColorMode > 0)
                        secondaryColor = m_effectManager->activeColorForIndex(secondaryColorMode);

                    if ( obj->m_groupCount > 0 ) {

						for (int j = 0; j < obj->m_groupCount; j++) {
							int groupID = obj->getGroupID(j);
							secondaryColor = m_effectManager->colorForGroupID(groupID, secondaryColor, false);
						}
                    }
                }

                if ( obj->m_detailColor->m_hsv.h != 0.0f
                  || obj->m_detailColor->m_hsv.s != 1.0f
                  || obj->m_detailColor->m_hsv.v != 1.0f
                  || obj->m_detailColor->m_hsv.absoluteSaturation )
                {
                    secondaryColor = m_effectManager->colorForEffect(secondaryColor, obj->m_detailColor->m_hsv);
				}

                obj->updateSecondaryColor(secondaryColor);
				float detailColorOpacity = m_effectManager->activeOpacityForIndex(secondaryColorMode);

                if (secondaryColorMode <= 0)
                    detailColorOpacity = 1.0f;
				
                if (obj->m_groupCount > 0) {

                    for (int j = 0; j < obj->m_groupCount; j++) {
                        int groupID = obj->getGroupID(j);
                        detailColorOpacity *= m_effectManager->opacityModForGroup(groupID);
                    }
                }
                obj->m_detailColor->m_opacity = detailColorOpacity;
            }

            if (obj->m_unk367)
                static_cast<AnimatedGameObject*>(obj)->updateChildSpriteColor(brightenedBGColor);
        }

        if (!m_previewMode && obj->isColorObject())
            editorOpacity *= 0.7f;

        if (m_previewMode && m_updateColorSprites && obj->m_colorSprite)
            obj->setOpacity(0);
		
        obj->setOpacity(editorOpacity);

        if (m_previewMode || !obj->m_updateEditorColor || obj->m_isSelected)
            obj->m_updateEditorColor = false;
        else
            obj->updateObjectEditorColor();

        obj->setPosition(obj->getRealPosition());
    }

    updateEnterEffects(dt);
    processAreaVisualActions(dt);
    updateParticles(dt);
    m_updateColorSprites = false;
    sortBatchnodeChildren(0.0f);
    updateKeyframeObjects();
    updateDebugDraw();
}