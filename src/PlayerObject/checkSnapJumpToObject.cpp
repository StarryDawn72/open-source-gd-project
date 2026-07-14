/*
	====== PlayerObject::checkSnapJumpToObject ======
	
	Runs every frame when the player is colliding with a solid
	object. It determines if you're going off sync when climbing or
	descending a specific set of staircases to nudge you back towards
	the center of the block and prevent you from eventually falling off.
	
*/
void PlayerObject::checkSnapJumpToObject(GameObject *object)
{
    
    if (!object) return;

    GameObject* previousObject = m_objectSnappedTo;
    GameObject* currentObject = object;

    if (
		previousObject != NULL &&
		previousObject->m_uniqueID != currentObject->m_uniqueID &&
		previousObject->getType() == GameObjectType::Solid
	) {

		CCPoint prevPos = previousObject->getRealPosition();
		CCPoint currPos = currentObject->getRealPosition();
		
		float speed = m_playerSpeed;
		float playerScale = m_vehicleSize;

		float stepUpDist = 120.0f;
		float stepDownDist = 150.0f;
		float doubleStepUpDist = 90.0f;
		float tolerance = 1.0f;

		if (speed == 0.9f) {
			if (playerScale != 1.0f) stepUpDist = 90.0f;
		}
		else if (speed == 0.7f) {
			stepUpDist = 90.0f;
			stepDownDist = 120.0f;
			doubleStepUpDist = 60.0f;
		}
		else if (speed == 1.1f) {
			stepUpDist = 150.0f;
			stepDownDist = 195.0f;
			doubleStepUpDist = 120.0f;
			tolerance = 2.0f;
			if (playerScale != 1.0f) stepUpDist = 90.0f;
		}
		else if (speed == 1.3f) {
			stepUpDist = 180.0f;
			stepDownDist = 225.0f;
			doubleStepUpDist = 135.0f;
			tolerance = 2.0f;
			if (playerScale != 1.0f) stepUpDist = 90.0f;
		}

		bool isStepUp = fabs(currPos.x - (prevPos.x + stepUpDist)) <= tolerance &&
						fabs(currPos.y - (prevPos.y + flipMod() * 30.f)) <= tolerance;

        bool isStepDown = fabs(currPos.x - (prevPos.x + stepDownDist)) <= tolerance &&
						  fabs(currPos.y - (prevPos.y - flipMod() * 30.f)) <= tolerance;

        bool isDoubleStepUp = fabs(currPos.x - (prevPos.x + doubleStepUpDist)) <= tolerance &&
							  fabs(currPos.y - (prevPos.y + flipMod() * 60.f)) <= tolerance;

		if (isStepUp || isStepDown || isDoubleStepUp) {

			float objX = object->getPosition().x;
			double finalX = objX + m_snapDistance;
			double playerX = getPosition().x;

			if (fabs(finalX - playerX) > (double)tolerance) {

				if (finalX <= playerX)
					finalX = playerX - (double)tolerance;
				else
					finalX = playerX + (double)tolerance;
			}

			setPosition(ccp(finalX, getPosition().y));			
		}
	}

    m_objectSnappedTo = object;
    m_snapDistance = getPosition().x - object->getPosition().x;
}