void PlayerObject::playDynamicSpiderRun()
{
    if (m_isDashing) return;

    if (m_playerSpeed <= 0.9f) {
        m_spiderSprite->runAnimation("walk");
    }
    else if (m_playerSpeed <= 1.1f) {
        m_spiderSprite->runAnimation("run");
        
        if (m_spiderSprite->m_animationManager->m_currentAnimation == "walk")
            m_spiderSprite->m_animationManager->offsetCurrentAnimation(0.1f);
    }
    else {
        const char* anim = m_spiderAnimation2Enabled ? "run2" : "run";
        m_spiderSprite->runAnimation(anim);

        if (m_spiderSprite->m_animationManager->m_currentAnimation == "walk")
            m_spiderSprite->m_animationManager->offsetCurrentAnimation(0.1f);
    }
}