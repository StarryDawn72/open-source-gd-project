/*
	Handles behavior for every object type when they collide with the player.
	The main collision resolution happens in checkCollisions (where this function's called).
*/
void GJBaseGameLayer::collisionCheckObjects(PlayerObject* object, std::vector<GameObject*>* objects, int objectCount, float dt)
{
	PlayerObject* player = object;

	GameObject*& player_m_lastEffectObject = player->m_lastActivatedPortal;
	CCPoint& player_m_lastEffectObjectPos = player->m_lastPortalPos;

	CCRect playerRect = player->getObjectRect();

	float playerMaxX = playerRect.getMaxX();
	float playerMinX = playerRect.getMinX();
	float playerMaxY = playerRect.getMaxY();
	float playerMinY = playerRect.getMinY();
	
	for (int i = 0; i < objectCount; i++) {
		GameObject* obj = (*objects)[i];
		GameObjectType type = obj->m_objectType;

		if (type == GameObjectType::Decoration || obj->m_isGroupDisabled || obj->m_isDisabled)
			continue;
		
		if (type == GameObjectType::Breakable || type == GameObjectType::Solid)
		{
			if (m_solidCollisionObjectsIndex > m_solidCollisionObjectsCount)
				m_solidCollisionObjects[m_solidCollisionObjectsCount] = obj;
			else {
				m_solidCollisionObjects.push_back(obj);
				m_solidCollisionObjectsIndex++;
			}
			m_solidCollisionObjectsCount++;
			continue;
		}

		if (type == GameObjectType::Hazard || type == GameObjectType::AnimatedHazard)
		{
			if (m_hazardCollisionObjectsIndex > m_hazardCollisionObjectsCount)
				m_hazardCollisionObjects[m_hazardCollisionObjectsCount] = obj;
			else {
				m_hazardCollisionObjects.push_back(obj);
				m_hazardCollisionObjectsIndex++;
			}
			m_hazardCollisionObjectsCount++;
			continue;
		}

		if (type == GameObjectType::CollisionObject)
			continue;

		if (obj->hasBeenActivatedByPlayer(player))
			continue;

		CCRect objectRect;

		if (type == GameObjectType::Slope)
			objectRect = obj->getObjectRect(2.0f, 2.0f);
		else
			objectRect = obj->getObjectRect();

		if (obj->m_objectRadius <= 0.0f)
		{
			if (
			   playerMaxX < objectRect.getMinX()
			|| playerMinX > objectRect.getMaxX()
			|| playerMaxY < objectRect.getMinY()
			|| playerMinY > objectRect.getMaxY())
			{
				// Not colliding
				continue;
			}
		}
		else if (!playerCircleCollision(player, obj))
			continue;
		
		bool colliding = true;

		if (obj->m_shouldUseOuterOb && (!m_levelSettings->m_fixRadiusCollision || obj->m_objectRadius <= 0.0f))
		{
			OBB2D* oldOB = obj->getOrientedBox();
			player->updateOrientedBox();
			OBB2D* newOB = player->getOrientedBox();

			colliding = oldOB->overlaps1Way(newOB) && newOB->overlaps1Way(oldOB);
		}

		if (obj->getType() == GameObjectType::Slope)
			objectRect = obj->getObjectRect();

		if (colliding && canTouchObject(obj)) {
			switch (obj->m_objectType) {
				case GameObjectType::InverseGravityPortal: {

					bool canBeActivated = canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj));
					bool noEffects = canBeActivated;
					if (canBeActivated) {

						if (!player->m_isUpsideDown && !obj->m_hasNoEffects)
							playGravityEffect(true);
						
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						if (!obj->m_hasNoEffects && obj->m_isHide)
							noEffects = true;

						flipGravity(player, true, noEffects);
						obj->playShineEffect();
						obj->activatedByPlayer(player);

						gameEventTriggered(GJGameEvent::PortalGravityFlip, 0, 0);
					}
					break;
				}
				case GameObjectType::NormalGravityPortal: {

					bool canBeActivated = canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj));
					bool noEffects = canBeActivated;

					if (canBeActivated) {

						if (player->m_isUpsideDown && !obj->m_hasNoEffects)
							playGravityEffect(false);
						
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						if (!obj->m_hasNoEffects && obj->m_isHide)
							noEffects = true;

						flipGravity(player, false, noEffects);
						obj->playShineEffect();
						obj->activatedByPlayer(player);

						gameEventTriggered(GJGameEvent::PortalGravityNormal, 0, 0);
					}
					break;
				}
				case GameObjectType::ShipPortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						playerWillSwitchMode(player, obj);
						switchToFlyMode(player, obj, false, static_cast<int>(GameObjectType::ShipPortal));
						obj->playShineEffect();
						obj->activatedByPlayer(player);
					}
					break;
				case GameObjectType::CubePortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
					{
						playerWillSwitchMode(player, obj);

						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;
						player->switchedToMode(GameObjectType::CubePortal);
						player->modeDidChange();

						obj->playShineEffect();
						obj->activatedByPlayer(player);
					}
					break;
				case GameObjectType::YellowJumpPad:
				case GameObjectType::PinkJumpPad:
				case GameObjectType::RedJumpPad:
				case GameObjectType::SpiderPad:
					bumpPlayer(player, static_cast<EffectGameObject*>(obj));
					break;
				case GameObjectType::GravityPad:
					gravBumpPlayer(player, static_cast<EffectGameObject*>(obj));
					break;
				case GameObjectType::YellowJumpRing:
				case GameObjectType::PinkJumpRing:
				case GameObjectType::GravityRing:
				case GameObjectType::GreenRing:
				case GameObjectType::DropRing:
				case GameObjectType::RedJumpRing:
				case GameObjectType::CustomRing:
				case GameObjectType::DashRing:
				case GameObjectType::GravityDashRing:
				case GameObjectType::SpiderOrb:
					playerTouchedRing(player, static_cast<RingObject*>(obj));
					break;
				case GameObjectType::InverseMirrorPortal:
					if (!m_isEditor && canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						toggleFlipped(true, obj->m_hasNoEffects);

						obj->playShineEffect();
						obj->triggerActivated(0.0f);

						gameEventTriggered(GJGameEvent::PortalFlip, 0, 0);
					}
					break;
				case GameObjectType::NormalMirrorPortal:
					if (!m_isEditor && canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						toggleFlipped(false, obj->m_hasNoEffects);
						obj->playShineEffect();
						obj->triggerActivated(0.0f);

						gameEventTriggered(GJGameEvent::PortalUnFlip, 0, 0);
					}
					break;
				case GameObjectType::BallPortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						playerWillSwitchMode(player, obj);
						switchToRollMode(player, obj, false);
						obj->playShineEffect();
						obj->activatedByPlayer(player);
					}
					break;
				case GameObjectType::RegularSizePortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						player->togglePlayerScale(false, obj->m_hasNoEffects);
						obj->playShineEffect();
						obj->activatedByPlayer(player);

						gameEventTriggered(GJGameEvent::PortalNormalScale, 0, 0);
					}
					break;
				case GameObjectType::MiniSizePortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						player->togglePlayerScale(true, obj->m_hasNoEffects);
						obj->playShineEffect();
						obj->activatedByPlayer(player);
						
						gameEventTriggered(GJGameEvent::PortalMiniScale, 0, 0);
					}
					break;
				case GameObjectType::UfoPortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
					{
						playerWillSwitchMode(player, obj);
						switchToFlyMode(player, obj, false, static_cast<int>(GameObjectType::UfoPortal));
						obj->playShineEffect();
						obj->activatedByPlayer(player);
					}
					break;
				case GameObjectType::Modifier:
				case GameObjectType::EnterEffectObject:
					playerTouchedTrigger(player, static_cast<EffectGameObject*>(obj));
					break;
				case GameObjectType::SecretCoin:
					if (!m_isPracticeMode) {
						obj->triggerObject(this, player->m_uniqueID, nullptr);
						obj->triggerActivated(0.0f);

						destroyObject(obj);

						if (!hasUniqueCoin(static_cast<EffectGameObject*>(obj)))
							pickupItem(static_cast<EffectGameObject*>(obj));

						gameEventTriggered(GJGameEvent::UserCoin, 0, 0);
					}
					break;
				case GameObjectType::DualPortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						m_player2->m_isBeingSpawnedByDualPortal = true;
						toggleDualMode(obj, true, player, false);
						m_player2->m_isBeingSpawnedByDualPortal = false;

						obj->playShineEffect();
						obj->triggerActivated(0.0f);

						gameEventTriggered(GJGameEvent::PortalDualOn, 0, 0);
					}
					break;
				case GameObjectType::SoloPortal:
					if (canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj))) {
						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						toggleDualMode(obj, false, player, false);
						obj->playShineEffect();
						obj->triggerActivated(0.0f);

						gameEventTriggered(GJGameEvent::PortalDualOff, 0, 0);
					}
					break;
				case GameObjectType::Slope:
					player->collidedWithSlope(dt, obj, false);
					playerRect =  player->getObjectRect();
					playerMaxX = playerRect.getMaxX();
					playerMinX = playerRect.getMinX();
					playerMaxY = playerRect.getMaxY();
					playerMinY = playerRect.getMinY();
					break;
				case GameObjectType::WavePortal:
					if (m_isPlatformer || !canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
						break;
					
					playerWillSwitchMode(player, obj);
					switchToFlyMode(player, obj, false, static_cast<int>(GameObjectType::WavePortal));
					obj->playShineEffect();
					obj->activatedByPlayer(player);
					break;
				case GameObjectType::RobotPortal:
					if (!canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
						break;

					playerWillSwitchMode(player, obj);
					switchToRobotMode(player, obj, false);
					obj->playShineEffect();
					obj->activatedByPlayer(player);
					break;
				case GameObjectType::TeleportPortal:
					if (!canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
						break;

					gameEventTriggered(GJGameEvent::PortalTeleport, 0, 0);
					teleportPlayer(static_cast<TeleportPortalObject*>(obj), player);
					playerRect =  player->getObjectRect();
					playerMaxX = playerRect.getMaxX();
					playerMinX = playerRect.getMinX();
					playerMaxY = playerRect.getMaxY();
					playerMinY = playerRect.getMinY();
					break;
				case GameObjectType::Collectible:
					if (m_effectManager->hasBeenTriggered(obj->m_uniqueID, 0)) {
						obj->triggerActivated(0.0f);
						destroyObject(obj);
						break;
					}

					m_effectManager->storeTriggeredID(obj->m_uniqueID, 0);
					if (obj->m_objectID == 1268) // spawn trigger
					{
						std::vector<int> remapKeys;
						static_cast<SpawnTriggerGameObject*>(obj)->updateRemapKeys(remapKeys);
					}

					obj->triggerObject(this, player->m_uniqueID, nullptr);
					gameEventTriggered(GJGameEvent::PickupItem, 0, 0);
					obj->triggerActivated(0.0f);
					destroyObject(obj);
					break;

				case GameObjectType::UserCoin:
					if (m_isPracticeMode)
						break;
					
					if (m_effectManager->hasBeenTriggered(obj->m_uniqueID, 0)) {
						obj->triggerActivated(0.0f);
						destroyObject(obj);
						break;
					}

					m_effectManager->storeTriggeredID(obj->m_uniqueID, 0);

					obj->triggerObject(this, player->m_uniqueID, nullptr);

					if (!hasUniqueCoin(static_cast<EffectGameObject*>(obj)))
						pickupItem(static_cast<EffectGameObject*>(obj));

					gameEventTriggered(GJGameEvent::UserCoin, 0, 0);
					obj->triggerActivated(0.0f);
					destroyObject(obj);
					break;
				case GameObjectType::SpiderPortal:
					if (!canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
						break;

					playerWillSwitchMode(player, obj);
					switchToSpiderMode(player, obj, false);
					obj->playShineEffect();
					obj->activatedByPlayer(player);
					break;
				case GameObjectType::Special:
					player->touchedObject(obj);
					break;
				case GameObjectType::SwingPortal:
					if (m_isPlatformer || !canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj)))
						break;

					playerWillSwitchMode(player, obj);
					switchToFlyMode(player, obj, false, static_cast<int>(GameObjectType::SwingPortal));
					obj->playShineEffect();
					obj->activatedByPlayer(player);
					break;
				case GameObjectType::GravityTogglePortal: {

					bool canBeActivated = canBeActivatedByPlayer(player, static_cast<EffectGameObject*>(obj));
					bool noEffects = canBeActivated;
					if (canBeActivated)
					{
						if (!obj->m_hasNoEffects)
							playGravityEffect(!player->m_isUpsideDown);

						player_m_lastEffectObjectPos = obj->getPosition();
						player_m_lastEffectObject = obj;

						if (!obj->m_hasNoEffects && obj->m_isHide)
							noEffects = true;

						flipGravity(player, !player->m_isUpsideDown, noEffects);
						
						obj->playShineEffect();
						obj->activatedByPlayer(player);
						gameEventTriggered(GJGameEvent::PortalGravityInvert, 0, 0);
					}
					break;
				}
				case GameObjectType::TeleportOrb:
					playerTouchedRing(player, static_cast<RingObject*>(obj));
					playerRect =  player->getObjectRect();
					playerMaxX = playerRect.getMaxX();
					playerMinX = playerRect.getMinX();
					playerMaxY = playerRect.getMaxY();
					playerMinY = playerRect.getMinY();
					break;
				default:
					break;
			}
		}
	}
}