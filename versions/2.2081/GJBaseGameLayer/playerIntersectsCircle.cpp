/*
    Standard overlap test against the player's circular hitbox and an object's circular hitbox.
*/
bool GJBaseGameLayer::playerIntersectsCircle(PlayerObject *player, GameObject *object)
{
    float dist = ccpDistance(player->getPosition(), object->getRealPosition());
    float radius = object->getObjectRadius();

    return dist <= (radius + (player->getObjectRect().size.width / 2));
}