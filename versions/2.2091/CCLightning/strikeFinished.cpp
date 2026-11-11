void CCLightning::strikeFinished()
{
    if (m_removeAfterFinished) removeMeAndCleanup();
}