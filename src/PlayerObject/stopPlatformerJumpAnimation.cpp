<<<<<<< HEAD
=======
// TODO: Find better names
#define kActionTagPlatformerJump0 13
#define kActionTagPlatformerJump1 14

>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
void PlayerObject::stopPlatformerJumpAnimation() {
    if (!m_isPlatformer)
        return;

    m_iconSprite->stopActionByTag(kActionTagPlatformerJump0);
    m_iconSprite->stopActionByTag(kActionTagPlatformerJump1);
    m_iconSprite->setScale(1.0f);
    m_iconGlow->stopActionByTag(kActionTagPlatformerJump0);
    m_iconGlow->stopActionByTag(kActionTagPlatformerJump1);
    m_iconGlow->setScale(1.0f);
<<<<<<< HEAD
}
=======
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
