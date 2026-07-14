/*
	====== PlayerObject::getModifiedSlopeYVel ======
	
	This function calculates the final Y velocity that the
	player needs to launch when exiting a slope. If it
	detects that you've been on the slope for less than 0.1
	seconds, it uses the time you've been on the slope as a
	final multiplier, capped to a minimum of 0.4.
	
*/
float PlayerObject::getModifiedSlopeYVel()
{
    double timeOnSlope = m_totalTime - m_slopeStartTime;
    double boostMod = 1.0f;

    if (timeOnSlope < 0.1f) {
        boostMod = MAX(0.4f, timeOnSlope * 10.0f);
    }

    return m_slopeYVelocity * boostMod;
}