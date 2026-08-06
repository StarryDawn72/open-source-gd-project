void PlayerObject::updateCollide(PlayerCollisionDirection direction, GameObject *object)
{
	float halfHeight = getObjectRect().size.height / 2;
	float halfWidth = getObjectRect().size.width / 2;

	switch (direction) { 
		case PlayerCollisionDirection::Top:
			updateCollideTop(getPosition().y + (halfHeight * flipMod()), object);
			break;
		case PlayerCollisionDirection::Bottom:
			updateCollideBottom(getPosition().y - (halfHeight * flipMod()), object);
			break;
		case PlayerCollisionDirection::Left:
			updateCollideLeft(getPosition().x - halfWidth, object);
			break;
		case PlayerCollisionDirection::Right:
			updateCollideRight(getPosition().x + halfWidth, object);
			break;
		default:
			break;
	}
}