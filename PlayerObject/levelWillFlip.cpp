/*
	====== PLAYEROBJECT::LEVELWILLFLIP ======
	
	Activates once when the player hits a mirror portal,
	right before the level horizontal flip animation occurs.
	It stops the player's drag particle, cuts off the player's
	trail, and fades out the streak. The player's drag effect and
	trail are resumed once the flipping is complete.
	
*/
void levelWillFlip()
{
    m_trailingParticles->setLife(m_trailingParticleLife * 0.3f);
    deactivateStreak(true);
}