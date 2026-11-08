bool PlayerObject::collidedWithObject(float dt, GameObject* object)
{
    return collidedWithObject(dt, object, CCRectZero, false);
}

bool PlayerObject::collidedWithObject(float dt, GameObject *object, cocos2d::CCRect *rect, bool skipCheck)
{
    if (m_isSideways)
        return handleRotatedCollisionInternal(dt, object, rect, skipCheck, false, false);
    else
        return collidedWithObjectInternal(dt, object, rect, skipCheck);
}