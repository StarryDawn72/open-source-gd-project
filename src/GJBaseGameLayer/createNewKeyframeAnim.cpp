CCArray* GJBaseGameLayer::createNewKeyframeAnim()
{
    auto group = CCArray::create();
    group->setTag(m_keyframeGroup);
    m_keyframeGroups->setObject(group, m_keyframeGroup);
    m_keyframeGroup++;
    return group;
}