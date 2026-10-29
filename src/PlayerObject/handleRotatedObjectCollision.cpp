// @version 2.2081
bool PlayerObject::handleRotatedObjectCollision(float dt, GameObject* object, CCRect rect, bool skipCheck)
{
    return handleRotatedCollisionInternal(dt, object, rect, skipCheck, false, false);
}
