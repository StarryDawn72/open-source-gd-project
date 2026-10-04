void GJGroundLayer::updateGround02Color(ccColor3B color)
{
    if (m_ground2Sprite) {
        CCArray* children = m_ground2Sprite->getChildren();

        if (children) {
            for (int i = 0; i < children->count(); i++) {
                CCSprite* sprite = (CCSprite*)children->objectAtIndex(i);
                sprite->setColor(color);
            }
        }
    }
}