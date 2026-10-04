void GJBaseGameLayer::bumpPlayer(PlayerObject* player, EffectGameObject* object) {

    if (canBeActivatedByPlayer(player, object)) {

        player->m_lastEffectObjectPos = object->getPosition() + ccp(0, -10);
        object->activatedByPlayer(player);

        float bumpMod = getBumpMod(player, (int)object->getType());

        player->m_lastEffectObject = object;

        if (object->m_isReverse)
            player->reversePlayer(object);

        player->bumpPlayer(bumpMod, (int)object->getType(), object->m_hasNoEffects, object);

        gameEventTriggered(objectTypeToGameEvent((int)object->getType()), 0, 0);
        gameEventTriggered(GJGameEvent::PadActivated, 0, 0);        
    }
}
