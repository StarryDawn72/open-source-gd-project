/*
	====== CCCircleWave::updatePosition ======
	
	Updates the effect's position to match the object
	it is following.
	
*/
void CCCircleWave::updatePosition(float dt)
{
	if (m_target) setPosition(m_target->getPosition());
}