void PlayerObject::rotateGameplayObject(GameObject* object)
{
    if (m_storedRotatedObjectOffsets.count(object->m_uniqueID) != 0)
        return;

    CCPoint objPos = object->getRealPosition();
    CCPoint plrPos = getPosition();

    float offsetX = (objPos.x - plrPos.x) * kWierdFactor - (objPos.y - plrPos.y) + plrPos.x - objPos.x;
    float offsetY = (objPos.x - plrPos.x) + (objPos.y - plrPos.y) * kWierdFactor + plrPos.y - objPos.y;

    object->addToTempOffset(offsetX, offsetY);
    object->setLastPosition(object->getLastPosition() + ccp(offsetX, offsetY));

    object->m_startRotationX -= 90.0f;
    object->m_startRotationY -= 90.0f;
    object->setRRotation(0);

    object->setObjectRectDirty(true);

    if (object->getType() == GameObjectType::Slope)
        object->determineSlopeDirection();

    m_storedRotatedObjectOffsets[object->m_uniqueID] = GJPointDouble(offsetX, offsetY);
}