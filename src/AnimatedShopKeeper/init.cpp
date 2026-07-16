/*
	====== AnimatedShopKeeper::init ======
	
	Standard initialization routine for all
	five shopkeepers.
	
*/

bool AnimatedShopKeeper::init(ShopType type)
{
    const char* def;

    m_type = type;
    switch (type) {
        case Secret:
            def = "GJShopKeeper2";
            break;
        case Community:
            def = "GJShopKeeper3";
            break;
        case Mechanic:
            def = "GJShopKeeper4";
            break;
        case Diamond:
            def = "GJShopKeeper5";
            break;
        default:
            def = "GJShopKeeper";
            break;
    }

    bool init = initWithType(def, nullptr, false);
    if (init) {
        m_idleInt2 = CC_RANDOM_0_1() * 5.0f + 10.0f; // range [10, 15]
        m_idleInt1 = CC_RANDOM_0_1() * 2.0f + 1.0f;  // range [1, 3]
        m_animationManager->stopAnimations();
    }
    return init;
}