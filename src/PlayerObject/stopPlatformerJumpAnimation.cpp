void PlayerObject::stopPlatformerJumpAnimation() {
    if (!m_isPlatformer)
        return;

    m_iconSprite->stopActionByTag(kActionTagPlatformerJump0);
    m_iconSprite->stopActionByTag(kActionTagPlatformerJump1);
    m_iconSprite->setScale(1.0f);
    m_iconGlow->stopActionByTag(kActionTagPlatformerJump0);
    m_iconGlow->stopActionByTag(kActionTagPlatformerJump1);
    m_iconGlow->setScale(1.0f);
}