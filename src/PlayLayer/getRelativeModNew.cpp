/*
	====== PlayLayer::getRelativeModNew ======
	
	This function calculates how close the given position
	is to the edges of the screen, normalized to a [0, 1] range.
	It's used in enter effects and invisible block calculations.
	
*/
float PlayLayer::getRelativeModNew(CCPoint position, float mod, float offset, bool unused, bool isRight)
{
	// Incorrect Geode bindings lol
	// The last two parameters are swapped
	isRight = unused;

	CCPoint cameraPos = m_gameState.m_cameraPosition2;
	float distanceFromEdge = 0.0f;

	if (isRight)
		distanceFromEdge = ((cameraPos.x + m_cameraWidth) - position.x) + mod;
	else
		distanceFromEdge = (position.x - cameraPos.x) - mod;

	return clampf(distanceFromEdge / position.y, 0.0f, 1.0f);
}