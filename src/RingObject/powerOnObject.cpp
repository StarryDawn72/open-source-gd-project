#define GM GameManager::sharedState()
/*
	====== RingObject::powerOnObject ======
	
	Activates this jump ring, and spawns a ripple effect
	under certain conditions.
	
*/
void RingObject::powerOnObject(int state)
{
	powerOnObject(state);

	if (!m_isRingPoweredOn && !GM->m_performanceMode && !GM->m_editorEnabled && !m_hasNoEffects) {
		spawnCircle();
	}
}