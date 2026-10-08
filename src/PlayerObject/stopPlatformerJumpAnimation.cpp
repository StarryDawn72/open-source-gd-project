#define kTagPlatformerJumpAnimation 13
#define kTagPlatformerJumpUnk 14 // TODO: find usage and name

void PlayerObject::stopPlatformerJumpAnimation() {
    if (!m_isPlatformer)
        return;

    m_iconSprite->stopActionByTag(kTagPlatformerJumpAnimation);
    m_iconSprite->stopActionByTag(kTagPlatformerJumpUnk);
    m_iconSprite->setScale(1.0f);
    m_iconGlow->stopActionByTag(kTagPlatformerJumpAnimation);
    m_iconGlow->stopActionByTag(kTagPlatformerJumpUnk);
    m_iconGlow->setScale(1.0f);
}
