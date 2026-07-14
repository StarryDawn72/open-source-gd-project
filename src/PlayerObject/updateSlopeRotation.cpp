/*
	====== PlayerObject::updateSlopeRotation ======
	
	This function runs every frame that the player is
	riding a slope's edge. It makes the player smoothly
	face the angle of the slope, or reset rotation entirely
	if you're in platformer mode and are undergoing a force from
	gravity on a slope greater than 80 degrees, presumably for the Robot.
	
*/
void PlayerObject::updateSlopeRotation(float dt)
{
	float targetSlopeAngle = m_slopeRotation;
	float rotationDegrees = convertToClosestRotation(CC_RADIANS_TO_DEGREES(targetSlopeAngle));

	// rename incorrect bindings
	double& lastPlatformerSlopeAngle = m_maybeChangedDirectionAngle;
	bool& slopeForceLeft = m_platformerMovingLeft;
	bool& slopeForceRight = m_platformerMovingRight;

	bool forcedByGravity = slopeForceLeft || slopeForceRight;

	if (m_isPlatformer && lastPlatformerSlopeAngle > 80.0f && forcedByGravity) {
		rotationDegrees = 0.0f;
	}

	updateRotation(dt, rotationDegrees);
}