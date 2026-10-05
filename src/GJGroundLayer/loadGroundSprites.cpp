void GJGroundLayer::loadGroundSprites(int count, bool floor)
{
    CCSprite* ground = floor ? m_ground1Sprite : m_ground2Sprite;

    if (!ground) return;

    CCArray* groundSprites = CCArray::create();

    if (ground->getChildren()) {
        groundSprites->addObjectsFromArray(ground->getChildren());
    }

    if (groundSprites->count() == count) return;

    if (groundSprites->count() >= count) {
        for (int i = groundSprites->count() - count; i > 0 && groundSprites->count(); i--)
        {
            ground->removeChild((CCNode*)groundSprites->lastObject(), true);
            groundSprites->removeLastObject(true);
        }
    }
    else {
        for (int i = groundSprites->count(); i < count; i++)
        {
            CCSprite* tile = CCSprite::createWithTexture(ground->getTexture());
            ground->addChild(tile);
            
            float y = floor ? -m_ground1Offset : 0.0f;

            tile->setPosition(ccp(i * tile->m_obRect.size.width, y));
            tile->setAnchorPoint(ccp(0.0f, 1.0f));
            tile->setColor(ccc3(166, 166, 166));
        }
    }
}