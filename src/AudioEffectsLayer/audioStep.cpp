#define PL GameManager::sharedState()->getPlayLayer()
/*
	====== AudioEffectsLayer::audioStep ======
	
	Called every frame while playing a level.
	It steps through the current array of pulses and 
	calls triggerEffect once it hits a time threshold
	to temporarily raise the audio scale for the given
	frequency. Used for the pulse effect on jump orbs,
	rods, and many other decorations.
	
*/
void AudioEffectsLayer::audioStep(float dt)
{
	m_timeElapsed += dt;
	CCArray* m_pulseQueue = m_unk1c0;

	if (m_pulseQueue && m_pulseQueue->count()) {
		CCString* time = static_cast<CCString*>(m_pulseQueue->objectAtIndex(0));

		if (time->floatValue() < m_timeElapsed) {
			CCString* pulse = static_cast<CCString*>(m_pulseQueue->objectAtIndex(1));
			float pulseValue = pulse->floatValue();

			// Remove the [time, pulse] pair
			m_pulseQueue->removeObjectAtIndex(0, true);
			m_pulseQueue->removeObjectAtIndex(0, true);

			if (!PL->m_isPracticeMode)
				triggerEffect(pulseValue);
		}
	}
}