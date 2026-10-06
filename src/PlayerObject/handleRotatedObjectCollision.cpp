bool PlayerObject::handleRotatedObjectCollision(
    float dt,
    GameObject* object,
    cocos2d::CCRect rect,
    bool skipCheck
) {
    return handleRotatedCollisionInternal(dt, object, rect, skipCheck, false, false);
}