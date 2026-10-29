// @version 2.2081
void PlayerObject::rotatePreSlopeObjects()
{
    for (const auto& [key, object] : m_potentialSlopeMap)
        rotateGameplayObject(object);
}