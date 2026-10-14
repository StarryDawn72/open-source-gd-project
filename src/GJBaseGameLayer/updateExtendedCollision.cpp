void GJBaseGameLayer::updateExtendedCollision(GameObject* object, bool extendedCollision)
{
    if (object->m_hasExtendedCollision == extendedCollision) {
        removeObjectFromSection(object);
        object->m_hasExtendedCollision = extendedCollision;
        addToSection(object);
    }
}