void GJBaseGameLayer::gravBumpPlayer(PlayerObject* player, EffectGameObject* object)
{
    bool targetDirection = !player->m_isSideways
        ? object->isFacingDown()
        : object->isFacingLeft();

    // Don't trigger gravity pad when gravity directions match
    if (player->m_isUpsideDown == targetDirection && canBeActivatedByPlayer(player, object)) {
        if (object->m_isReverse)
            player->reversePlayer(object);

        if (!object->m_hasNoEffects)
            this->playGravityEffect(!targetDirection);

        player->m_lastPortalPos = object->getPosition() + ccp(0.0f, -10.0f);
        object->activatedByPlayer(player);
        player->m_lastEffectObject = object;
        player->propellPlayer(0.8f, object->m_hasNoEffects, 10);

        flipGravity(player, !targetDirection, true);
        player->m_canDisableAutoJump = true;
        gameEventTriggered(GJGameEvent::GravityPad, 0, 0);
    }
}