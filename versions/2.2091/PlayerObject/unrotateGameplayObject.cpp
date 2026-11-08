void PlayerObject::unrotateGameplayObject(GameObject* object)
{
    if (m_storedRotatedObjectOffsets.count(object->m_uniqueID) == 0)
        return;

    GJPointDouble& offset = m_storedRotatedObjectOffsets[object->m_uniqueID];

    object->addToTempOffset(-offset.m_x, -offset.m_y);
    object->setLastPosition(object->getLastPosition() + ccp(-offset.m_x, -offset.m_y));

    object->m_startRotationX += 90.0f;
    object->m_startRotationY += 90.0f;
    object->setRRotation(0.0f);

    if (object->getType() == GameObjectType::Slope)
        object->determineSlopeDirection();

    m_storedRotatedObjectOffsets.erase(object->m_uniqueID);
}