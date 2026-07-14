/*
	====== PlayerObject::isSafeMode ======
	
	Returns true if the time since the game mode
	change is less than the given time.
	
*/
bool PlayerObject::isSafeMode(float changeTime)
{
    return m_gameModeChangedTime != 0.0 &&
		   m_totalTime - m_gameModeChangedTime < (double)changeTime;
}