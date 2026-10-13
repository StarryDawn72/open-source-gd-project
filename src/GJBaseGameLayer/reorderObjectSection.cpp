void GJBaseGameLayer::reorderObjectSection(GameObject* object)
{
    removeObjectFromSection(object);
    addToSection(object);
}