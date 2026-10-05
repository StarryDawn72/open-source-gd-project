GJGroundLayer* GJGroundLayer::create(int groundID, int lineType)
{
    GJGroundLayer* ret = new GJGroundLayer();

    if (ret->init(groundID, lineType)) {
        ret->autorelease();
        return ret;
    }

    ret = NULL;
    return ret;
}