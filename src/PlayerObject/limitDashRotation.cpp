/*
	====== PlayerObject::limitDashRotation ======
	
	Limits the dash angle in classic mode to ±70 degrees, preventing
	the player from shooting up into the world ceiling from a near-vertical
	dash ring.
	
*/
void PlayerObject::limitDashRotation(float& rotation)
{
	float limit = 70.0f;
    float offset = m_isSideways ? -90.0f : 0.0f;
    if (m_isGoingLeft) offset += 180.0f;

    if (offset != 0.0f) {
        rotation += offset;
        snapRotation360(rotation);
    }

    if (fabs(rotation) > 90.0f) {
        float baseRotation = (rotation <= 0.0f) ? -180.0f : 180.0f;
        rotation = baseRotation - rotation;
        snapRotation360(rotation);
    }

    if (rotation > limit)
		rotation = (rotation >= 180.0f) ? -limit : limit;
    else if (rotation < -limit)
		rotation = (rotation > -180.0f) ? -limit : limit;

    if (offset != 0.0f) {
        rotation -= offset;
        snapRotation360(rotation);
    }
}