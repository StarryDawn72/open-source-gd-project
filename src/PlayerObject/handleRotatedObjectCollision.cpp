<<<<<<< HEAD
bool PlayerObject::handleRotatedObjectCollision(
    float dt,
    GameObject* object,
    cocos2d::CCRect rect,
    bool skipCheck
) {
    return handleRotatedCollisionInternal(dt, object, rect, skipCheck, false, false);
}
=======
bool PlayerObject::handleRotatedObjectCollision(float dt, GameObject* object, CCRect rect, bool skipCheck)
{
    return handleRotatedCollisionInternal(dt, object, rect, skipCheck, false, false);
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
