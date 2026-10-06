#define PL GameManager::sharedState()->getPlayLayer()

void PlayerObject::removePlacedCheckpoint()
{
    if (m_checkpointTimeout)
    {
        PL->removeCheckpoint(false);
        m_checkpointTimeout = false;
    }
}
