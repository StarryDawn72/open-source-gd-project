void PlayerObject::playingEndEffect()
{
    if (m_isSpider)
        m_spiderSprite->tweenToAnimation("fall_loop", 0.4);
}