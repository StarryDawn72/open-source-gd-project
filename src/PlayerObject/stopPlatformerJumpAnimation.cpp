// TODO: Find better names
#define kActionTagPlatformerJumpAnimation 13
#define kActionTagPlatformerJumpUnk 14

void PlayerObject::stopPlatformerJumpAnimation() {
    if (!m_isPlatformer)
        return;

    m_iconSprite->stopActionByTag(kActionTagPlatformerJumpAnimation);
    m_iconSprite->stopActionByTag(kActionTagPlatformerJumpUnk);
    m_iconSprite->setScale(1.0f);
    m_iconGlow->stopActionByTag(kActionTagPlatformerJumpAnimation);
    m_iconGlow->stopActionByTag(kActionTagPlatformerJumpUnk);
    m_iconGlow->setScale(1.0f);
}
