bool PlayerObject::testForMoving(float dt, GameObject* object)
{
    CCPoint lastPos = object->getLastPosition();
    CCPoint currPos = object->getRealPosition();
    
    if (currPos.x == lastPos.x && currPos.y == lastPos.y)
        return false;

    if ((!m_isUpsideDown && lastPos.y <= currPos.y) || // Object is moving down
        (m_isUpsideDown  && lastPos.y >= currPos.y)    // Object is moving up
    ) return false;

    // Proceed if the object is launching the player up

    float margin = dt * 5.0f;

    CCRect oRect = object->getObjectRect();
    oRect.size.height = oRect.size.height + margin;

    if (m_isUpsideDown)
        oRect.origin.y = oRect.origin.y - margin;

    if (getObjectRect().intersectsRect(oRect)) {
        this->m_collidedObject = object;
        return true;
    }

    return false;
}