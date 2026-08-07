void PlayerObject::updateRobotAnimationSpeed()
{
	float m_playerScale = m_vehicleSize;

    float baseSpeed = 1.0f;

    if      (m_playerSpeed == 0.9f) baseSpeed = 1.0f;
	else if (m_playerSpeed == 0.7f) baseSpeed = 0.9f;
	else if (m_playerSpeed == 1.1f) baseSpeed = 1.15f;
	else if (m_playerSpeed == 1.3f) baseSpeed = 1.3f;
	else if (m_playerSpeed == 1.6f) baseSpeed = 1.5f;

	float robotScaleMod = (m_playerScale < 1.0f) ? 0.85f : 1.0f;
	float spiderScaleMod = (m_playerSpeed < 1.1f) ? robotScaleMod : robotScaleMod * 1.1f;

    m_robotSprite->m_animationManager->updateAnimationSpeed(baseSpeed / robotScaleMod);
    m_spiderSprite->m_animationManager->updateAnimationSpeed(baseSpeed / spiderScaleMod);

    if (m_isSpider) {
		gd::string currentAnim = m_spiderSprite->m_animationManager->m_currentAnimation;
		if (currentAnim == "walk" || currentAnim == "run")
			playDynamicSpiderRun();
	}

	gd::string newAnim;

    if (m_robotAnimation1Enabled && m_playerSpeed == 0.7f)
        newAnim = "run3";
    else if (m_robotAnimation2Enabled && (m_playerSpeed == 1.3f || m_playerSpeed == 1.6f))
        newAnim = "run2";
    else
        newAnim = "run";

	m_currentRobotAnimation = newAnim;

    if (m_isRobot) {
        if (m_currentRobotAnimation != m_robotSprite->m_animationManager->m_currentAnimation) {
            m_robotSprite->runAnimation(m_currentRobotAnimation);
        }
    }
}