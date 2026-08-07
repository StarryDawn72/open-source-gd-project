void PlayerObject::unrotatePreSlopeObjects()
{
	std::unordered_map<int, GameObject*>& m_preSlopeObjects = m_potentialSlopeMap;

    for (auto& entry : m_preSlopeObjects) {
        unrotateGameplayObject(entry.second);
    }
}