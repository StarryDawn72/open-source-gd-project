void PlayerObject::handleRotatedSlopeCollision(float dt, GameObject* object, bool skipPre)
{
    handleRotatedCollisionInternal(dt, object, CCRectZero, false, skipPre, true);
}