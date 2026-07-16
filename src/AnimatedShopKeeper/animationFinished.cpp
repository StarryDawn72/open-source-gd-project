/*
	====== AnimatedShopKeeper::animationFinished ======
	
	State machine that handles randomized idle animations
	for the shopkeepers. Runs after any animation is done playing.
	
*/

void AnimatedShopKeeper::animationFinished(const char* key)
{
	m_idleInt1--;
	m_idleInt2--;
	gd::string keyString = gd::string(key);

	if (keyString == "react01")
		m_reacting = false;

	if (keyString != "idle03" && m_idleInt2 <= 0 && m_type != ShopType::Diamond) {
		m_looking = false;
		m_idleInt2 = CCRANDOM_0_1() * 5.0f + 10.0f; // range [10, 15]
		runAnimationForced("idle03");
		return;
	}

	bool shouldReactIdle = (keyString == "idle00") && (m_idleInt1 <= 0);

	if (shouldReactIdle) {
		if (CCRANDOM_0_1() <= 0.9f || m_type == ShopType::Diamond)
			runAnimationForced("idle02");
		else
			runAnimationForced("idle01");
		m_idleInt1 = CCRANDOM_0_1() * 3.0f + 2.0f;
		return;
	}

	bool shouldLook = (keyString == "idle03" && !m_looking) && (CCRANDOM_0_1() > 0.6f);
	if (!shouldLook) {
		runAnimationForced("idle00");
		return;
	}

	runAnimationForced("idle03");
	m_looking = true;
}