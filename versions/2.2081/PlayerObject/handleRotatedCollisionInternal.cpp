bool PlayerObject::handleRotatedCollisionInternal(float dt, GameObject* object, CCRect rect, bool skipCheck, bool skipPre, bool slope)
{
    CCPoint oldPos = getPosition();
    rotateGameplayObject(object);
    rotatePreSlopeObjects();

    bool ret = false;
    if (slope)
        collidedWithSlopeInternal(dt, object, skipPre);
    else
        ret = collidedWithObjectInternal(dt, object, rect, skipCheck);

    CCPoint newPos = getPosition();
    setPosition(ccp(
        oldPos.x + (newPos.y - oldPos.y),
        oldPos.y - (newPos.x - oldPos.x)
    ));

    unrotateGameplayObject(object);
    unrotatePreSlopeObjects();
    return ret;
}