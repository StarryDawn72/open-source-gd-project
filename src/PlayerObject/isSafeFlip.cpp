/*
	====== PlayerObject::isSafeFlip ======
	
	Returns true if the time since the last gravity
	switch is less than the given time.
	
*/
bool PlayerObject::isSafeFlip(float flipTime)
{
    return m_lastFlipTime != 0.0 &&
		   m_totalTime - m_lastFlipTime < (double)flipTime;
}