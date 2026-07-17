/*
	====== AnimatedShopKeeper::create ======
	
	Create factory for all five shopkeepers.
	
*/

AnimatedShopKeeper *AnimatedShopKeeper::create(ShopType type)
{
    AnimatedShopKeeper* ret = new AnimatedShopKeeper();

    if (ret->init(type)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}