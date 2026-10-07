<<<<<<< HEAD
=======
#define PL GameManager::sharedState()->getPlayLayer()

>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
void PlayerObject::removePlacedCheckpoint()
{
    if (m_checkpointTimeout)
    {
        PL->removeCheckpoint(false);
        m_checkpointTimeout = false;
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
