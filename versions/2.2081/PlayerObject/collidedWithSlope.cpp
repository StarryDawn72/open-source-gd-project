void PlayerObject::collidedWithSlope(float dt, GameObject *object, bool skipPre)
{
    if (m_isSideways)
        handleRotatedSlopeCollision(dt, object, skipPre);
    else
        collidedWithSlopeInternal(dt, object, skipPre);
}