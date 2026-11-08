PlayerObject* PlayerObject::create(int player, int ship, GJBaseGameLayer *gameLayer, CCLayer *layer, bool playLayer)
{
    PlayerObject* ret = new PlayerObject();
    if (ret->init(player, ship, gameLayer, layer, playLayer)) {
        ret->autorelease();
		return ret;
    }
	delete ret;
	return nullptr;
}