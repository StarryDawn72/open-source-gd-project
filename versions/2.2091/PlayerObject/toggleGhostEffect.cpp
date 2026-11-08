void PlayerObject::toggleGhostEffect(GhostType type)
{
    if (m_ghostType != type) {
        m_ghostType = type;

        if (m_ghostTrail) {
            m_ghostTrail->stopTrail();
            m_ghostTrail = nullptr;
        }
        if (m_ghostType == GhostType::Enabled) {
            ccColor3B iconColor = m_iconSprite->getColor();

			if (iconColor.r == 0 && iconColor.g == 0 && iconColor.b == 0) {
				GhostTrailEffect* effect = GhostTrailEffect::create();
                m_ghostTrail = effect;
                m_ghostTrail->m_playerObject = this;
                m_ghostTrail->m_playerScale = m_vehicleSize;

                m_ghostTrail->m_opacity = 200.0f;
                m_ghostTrail->m_color = ccBLACK;

                m_ghostTrail->runWithTarget(m_iconSprite, 0.05f, 0.4f, 0.0f, 0.6f, false);
			}
			else {
				GhostTrailEffect* effect = GhostTrailEffect::create();
                m_ghostTrail = effect;
                m_ghostTrail->m_playerObject = this;
                m_ghostTrail->doBlendAdditive();
                m_ghostTrail->m_playerScale = m_vehicleSize;

                m_ghostTrail->m_opacity = 200.0;
                m_ghostTrail->m_color = m_playerColor1;

                m_ghostTrail->runWithTarget(m_iconSprite, 0.05f, 0.4f, 0.0f, 0.6f, false);
			}

            m_ghostTrail->m_objectLayer = PL->m_objectLayer;
            PL->m_objectLayer->addChild(m_ghostTrail);
        }
    }
}