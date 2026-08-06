void PlayerObject::setFlipX(bool flipX)
{
    GameObject::setFlipX(flipX);
    m_iconSprite->setFlipX(flipX);
    m_iconSpriteSecondary->setFlipX(flipX);
    m_vehicleSprite->setFlipX(flipX);
    m_vehicleSpriteSecondary->setFlipX(flipX);
    m_birdVehicle->setFlipX(flipX);
    m_vehicleGlow->setFlipX(flipX);
}