void GJBaseGameLayer::removeKeyframe(KeyframeGameObject* object)
{
    auto group = (CCArray*)m_keyframeGroups->objectForKey(object->m_keyframeGroup);
    if (group) {
        group->removeObject(object, true);
        updateKeyframeOrder(object->m_keyframeGroup);
    }
}