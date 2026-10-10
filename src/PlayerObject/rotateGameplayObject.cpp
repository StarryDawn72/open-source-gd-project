void PlayerObject::rotateGameplayObject(GameObject* object)
{
    if (m_storedRotatedObjectOffsets.count(object->m_uniqueID) != 0)
        return;

    CCPoint objPos = object->getRealPosition();
    CCPoint plrPos = getPosition();

    float offsetX = (objPos.x - plrPos.x) * -0.00000004371139f - (objPos.y - plrPos.y) + plrPos.x - objPos.x; // TODO: figure out the number
    float offsetY = (objPos.x - plrPos.x) + (objPos.y - plrPos.y) * -0.00000004371139f + plrPos.y - objPos.y;

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
