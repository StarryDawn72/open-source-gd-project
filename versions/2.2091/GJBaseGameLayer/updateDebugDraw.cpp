/*
    Draws player and object hitboxes in an inefficient way.
*/
void GJBaseGameLayer::updateDebugDraw()
{
    m_debugDrawNode->clear();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    float zoom = m_objectLayer->getScaleX();
    float absZoom = fabsf(zoom);
    float strokeWidth = 0.25f / absZoom;
    
    CCPoint cameraPos = m_objectLayer->getPosition();

    float x = (zoom < 0) ? cameraPos.x - winSize.width : -cameraPos.x;

    CCRect drawArea = CCRectMake(
        x / absZoom,
        -cameraPos.y / absZoom,
        winSize.width / absZoom, 
        winSize.height / absZoom
    );

    float cameraAngle = m_gameState.m_cameraAngle;
    if (cameraAngle != 0) {

        float cosA = fabsf(cosf(CC_DEGREES_TO_RADIANS(cameraAngle)));
        float sinA = fabsf(sinf(CC_DEGREES_TO_RADIANS(cameraAngle)));
        float padX = (drawArea.size.height * sinA) + (drawArea.size.width * cosA) - drawArea.size.width;
        float padY = (drawArea.size.height * cosA) + (drawArea.size.width * sinA) - drawArea.size.height;

        drawArea.origin.x -= padX / 2;
        drawArea.origin.y -= padY / 2;
        drawArea.size.width += padX;
        drawArea.size.height += padY;
    }

    m_debugDrawNode->enableDrawArea(drawArea);

    int totalSections = m_sections.empty() ? -1 : (int)m_sections.size();

    if (shouldDrawDebugHitboxes()) {
        for (int x = m_leftSectionIndex; x <= m_rightSectionIndex && x < totalSections; x++) {
            std::vector<std::vector<GameObject*>*>* xSection = m_sections[x];

            int ySections = xSection == NULL ? -1 : (int)m_sections[x]->size();
            for (int y = m_bottomSectionIndex; y <= m_topSectionIndex && y < ySections; y++) {

                std::vector<GameObject*>* sec = (*m_sections[x])[y];
                if (!sec) continue;

                int objectCount = (*m_sectionSizes[x])[y];
                for (int i = 0; i < objectCount; i++) {

                    GameObject* obj = (*sec)[i];
                    GameObjectType type = obj->m_objectType;

                    if (!obj->m_isActivated && !m_isEditor) continue;
                    if (type == GameObjectType::Decoration) continue;
                    if (m_playbackMode != PlaybackMode::Not && obj->m_isGroupDisabled) continue;

                    if (obj->m_objectRadius > 0) {
                        if (type == GameObjectType::Hazard) {
                            CCPoint pos = obj->getPosition();
                            unsigned int segments = MAX(obj->getObjectRadius(), 8);
                            m_debugDrawNode->drawCircle(
                                pos,
                                obj->getObjectRadius(),
                                ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                                strokeWidth,
                                ccc4f(1.f, 0.f, 0.f, 1.f), // opaque red
                                segments);
                        }
                        continue;
                    }

                    if (obj->getType() == GameObjectType::Slope) {
                        CCRect r = obj->getObjectRect();
                        obj->determineSlopeDirection();

                        CCPoint* verts = new CCPoint[3];

                        verts[0] = ccp(r.origin.x, r.origin.y);
                        verts[1] = ccp(r.origin.x, r.origin.y + r.size.height);
                        verts[2] = ccp(r.origin.x + r.size.width, r.origin.y);
                        CCPoint corner = ccp(r.origin.x + r.size.width, r.origin.y + r.size.height);

                        switch (obj->m_slopeDirection) {
                            case 0: case 7: verts[1] = corner; break;
                            case 1: case 5: verts[0] = corner; break;
                            case 3: case 6: verts[2] = corner; break;
                            default: break;
                        }

                        m_debugDrawNode->drawPolygon(
                            verts,
                            3,
                            ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                            strokeWidth,
                            obj->m_isGripSlope
                                ? ccc4f(1.f, 0.25f, 1.f, 1.f) // opaque magenta
                                : ccc4f(1.f, 0.f, 1.f, 1.f) // opaque blue
                            ,
                            BorderAlignment::Outside);

                        delete[] verts;
                        continue;
                    }

                    ccColor4F color = ccc4f(0.f, 0.25f, 1.f, 1.f); // blue
                    
                    if (obj->getType() == GameObjectType::Hazard || obj->getType() == GameObjectType::AnimatedHazard) {
                        color = ccc4f(1.f, 0.f, 0.f, 1.f); // red
                    }
                    else if (obj->getType() != GameObjectType::Solid) {
                        if (!obj->m_greenDebugDraw) continue;
                        color = ccc4f(0.f, 1.f, 0.f, 1.f); // green
                    }
                    else if (obj->m_isPassable) {
                        color = ccc4f(0.f, 1.f, 1.f, 1.f); // cyan
                    }

                    if (obj != m_anticheatSpike) {
                        bool wasObjectRectDirty = obj->m_isObjectRectDirty;
                        bool wasBoxOffsetCalculated = obj->m_boxOffsetCalculated;

                        CCRect rect = obj->getObjectRect();

                        if ((int)obj->getRotation() % 90 != 0 && (m_isEditor || obj->m_shouldUseOuterOb)) {
                            obj->calculateOrientedBox();

                            m_debugDrawNode->drawPolygon(
                                obj->getOrientedBox()->m_corners.data(),
                                4,
                                ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                                strokeWidth,
                                color,
                                BorderAlignment::Outside);
                        }
                        else {

                            m_debugDrawNode->drawRect(
                                rect.origin,
                                ccp(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height),
                                ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                                strokeWidth,
                                color,
                                BorderAlignment::Outside);
                        }

                        obj->m_isObjectRectDirty = wasObjectRectDirty;
                        obj->m_boxOffsetCalculated = wasBoxOffsetCalculated;
                    }
                }
            }
        }

        if (!m_isEditor && (!m_disablePlayerHitbox || m_hitboxesOnDeath && m_playerDied) && (!m_playerDied || !shouldDrawHitboxTrail())) {
            m_player1->updateOrientedBox();
            if (m_player1->m_isBall) {
                m_debugDrawNode->drawRect(
                    m_player1->getObjectRect(),
                    ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                    strokeWidth,
                    ccc4f(1.f, 1.f, 0.f, 1.f), // yellow
                    BorderAlignment::Outside);
            }
            else {
                m_debugDrawNode->drawPolygon(m_player1->getOrientedBox()->m_corners.data(),
                    4,
                    ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                    strokeWidth,
                    ccc4f(1.f, 1.f, 0.f, 1.f), // yellow
                    BorderAlignment::Outside);
            }

            if (m_gameState.m_isDualMode) {
                m_player2->updateOrientedBox();
                
                if (m_player2->m_isBall) {
                    m_debugDrawNode->drawRect(
                        m_player2->getObjectRect(),
                        ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                        strokeWidth,
                        ccc4f(1.f, 1.f, 0.f, 1.f), // yellow
                        BorderAlignment::Outside);
                }
                else {
                    m_debugDrawNode->drawPolygon(
                        m_player2->getOrientedBox()->m_corners.data(),
                        4,
                        ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                        strokeWidth,
                        ccc4f(1.f, 1.f, 0.f, 1.f), // yellow
                        BorderAlignment::Outside);
                }
            }

            if (m_hitboxesOnDeath && m_playerDied) {
                CCRect r1 = m_player1->getObjectRect();

                m_debugDrawNode->drawRect(
                    r1.origin,
                    ccp(r1.origin.x + r1.size.width, r1.origin.y + r1.size.height),
                    ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                    strokeWidth,
                    ccc4f(1.f, 1.f, 0.f, 0.5f), // semi-transparent yellow
                    BorderAlignment::Outside);

                if (m_gameState.m_isDualMode) {
                    CCRect r2 = m_player2->getObjectRect();

                    m_debugDrawNode->drawRect(
                        r2.origin,
                        ccp(r2.origin.x + r2.size.width, r2.origin.y + r2.size.height), 
                        ccc4f(0.f, 0.f, 0.f, 0.f), // transparent fill
                        strokeWidth,
                        ccc4f(1.f, 1.f, 0.f, 0.5f), // semi-transparent yellow
                        BorderAlignment::Outside);
                }
            }
        }
    }

    if (!shouldDrawHitboxTrail()) {
        
        if (!m_hitboxTrailDrawn)
            return;

        m_debugDrawNode2->clear();
        m_hitboxTrailDrawn = false;
        m_hitboxTrailDirty = true;

        return;
    }

    if (m_hitboxTrailDirty || !m_hitboxTrailDrawArea.equals(drawArea) || m_lastHitboxTrailHighlight != m_hitboxTrailHighlight || m_lastHitboxTrailDied != m_playerDied) {

        m_debugDrawNode2->clear();
        m_debugDrawNode2->enableDrawArea(drawArea);
        drawHitboxTrail(m_player1HitboxTrail, m_player1HitboxTrailLimit, drawArea, strokeWidth);
        drawHitboxTrail(m_player2HitboxTrail, m_player2HitboxTrailLimit, drawArea, strokeWidth);
        m_hitboxTrailDirty = false;
        m_hitboxTrailDrawn = true;

        m_hitboxTrailDrawArea = drawArea;
        m_lastHitboxTrailHighlight = m_hitboxTrailHighlight;
        m_lastHitboxTrailDied = m_playerDied;
    }
}