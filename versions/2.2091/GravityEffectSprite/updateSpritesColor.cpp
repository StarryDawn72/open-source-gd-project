void GravityEffectSprite::updateSpritesColor(ccColor3B color)
{
    CCNode* batchNode = getChildByTag(kTagGravityEffectBatch);

    if (batchNode) {
        CCArray* sprites = batchNode->getChildren();

        for (int i = 0; i < sprites->count(); i++) {
            ((CCSprite*)sprites->objectAtIndex(i))->setColor(color);
        }
    }
}