/*
	====== AnimatedShopKeeper::playReactAnimation ======
	
	This function triggers the react animation when you
	interact with the regular shopkeeper. It does not trigger
	on any others despite them all being instances of the same 
	"AnimatedShopKeeper" class.
	
*/
void AnimatedShopKeeper::playReactAnimation()
{
	if ( !m_reacting )
	{
		m_gruntIndex++;
		if (m_gruntIndex > 3) m_gruntIndex = 1;

		gd::string path = CCString::createWithFormat("grunt0%i.ogg", m_gruntIndex)->getCString();
		FMODAudioEngine::sharedEngine()->playEffect(path, 1.0f, 0.0f, 0.65f);

		runAnimationForced("react01");
		m_reacting = true;
		m_reactCount++;
	}
}