/*
	====== PLAYEROBJECT::UPDATESLOPEROTATION ======
	
	This function runs every frame that the player is
	riding a slope's edge. It makes the player smoothly
	face the angle of the slope, or reset rotation entirely
	if you're in platformer mode and are undergoing a force from
	gravity on a slope greater than 80 degrees.
	
*/
void PlayerObject::updateSlopeRotation(float dt)
{
	float targetSlopeAngle = m_slopeRotation;
	float rotationDegrees = convertToClosestRotation(CC_RADIANS_TO_DEGREES(targetSlopeAngle));

	// rename incorrect bindings
	double lastPlatformerSlopeRotation = m_maybeChangedDirectionAngle;
	bool slopeForceRight = m_platformerMovingRight;
	bool slopeForceLeft = m_platformerMovingLeft;

	if (m_isPlatformer && lastPlatformerSlopeRotation > 80.0f && (slopeForceRight || slopeForceLeft)) {
		rotationDegrees = 0.0f;
	}

	updateRotation(dt, rotationDegrees);
}