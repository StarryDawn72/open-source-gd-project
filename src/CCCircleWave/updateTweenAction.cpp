/*
	====== CCCircleWave::updateTweenAction ======

	Apply a tweened value update to the circle wave. Ran
	every frame.
*/
void CCCircleWave::updateTweenAction(float value, const char *key)
{
	gd::string keyString = gd::string(key);

	if (keyString == "opacity") m_opacity = value;
	else if (keyString == "radius") m_radius = value;

	if (m_target) setPosition(m_target->getPosition());
}