/*
	====== AnimatedShopKeeper::create ======
	
	Create factory for all five shopkeepers.
	
*/

AnimatedShopKeeper *AnimatedShopKeeper::create(ShopType type)
{
    AnimatedShopKeeper* ret = new AnimatedShopKeeper();

    ret->m_animationManager = nullptr;
    ret->m_sprite = nullptr;
    ret->m_fbfSprite = nullptr;
    ret->m_paSprite = nullptr;
    ret->m_spriteMode = 0;
    ret->m_delegate = nullptr;
    ret->m_type = 0;
    ret->m_idleInt1 = 0;
    ret->m_idleInt2 = 0;
    ret->m_looking = 0;
    ret->m_reacting = 0;
    ret->m_reactCount = 0;
    ret->m_gruntIndex = 0;

    if (ret->init(type)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}