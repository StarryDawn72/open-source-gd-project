void PlayerObject::unrotatePreSlopeObjects()
{
    for (auto& object : m_preSlopeObjects) {
        unrotateGameplayObject(object.second);
    }
}