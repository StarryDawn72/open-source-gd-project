void PlayerObject::removePendingCheckpoint()
{
    if (m_pendingCheckpoint)
    {
        GameObject* object = m_pendingCheckpoint->getObject();
        object->removeGlow();
        object->removeMeAndCleanup();
        m_pendingCheckpoint->release();
        m_pendingCheckpoint = nullptr;
    }
}