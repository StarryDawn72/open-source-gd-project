void GJGroundLayer::updateGround01Color(ccColor3B color)
{
    CCArray* children = this->m_ground1Sprite->getChildren();

    if (children) {
        for (int i = 0; i < children->count(); i++) {
            CCSprite* sprite = (CCSprite*)children->objectAtIndex(i);
            sprite->setColor(color);
        }
    }
}