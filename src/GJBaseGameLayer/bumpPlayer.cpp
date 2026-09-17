void GJBaseGameLayer::bumpPlayer(PlayerObject* player, EffectGameObject* object) {
    if (!canBeActivatedByPlayer(player, object))
        return;

    player.m_lastPortalPosition = object->getPosition() + ccp(0, -10);

    object->activatedByPlayer(player);

    float bumpMod = getBumpMod(player, object->getType());

    player->m_lastActivatedPortal = object;

    if (object->m_isReverse)
        player->reversePlayer(object);

    player->bumpPlayer(bumpMod, object->getType(), object->m_hasNoEffects, object);

    gameEventTriggered(objectTypeToGameEvent(object->getType()), 0, 0);
    gameEventTriggered(GJGameEvent::PadActivated, 0, 0);
}