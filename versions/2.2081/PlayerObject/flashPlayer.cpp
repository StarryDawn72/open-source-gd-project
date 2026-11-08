void PlayerObject::flashPlayer(float flashDuration, float flashDelay, ccColor3B mainColor, ccColor3B secondColor)
{
    m_flashMainColor = mainColor;
    m_flashSecondColor = secondColor;

    setColor(m_flashMainColor);
    setSecondColor(m_flashSecondColor);

    m_flashTime = m_totalTime;
    m_flashDuration = flashDuration;
    m_flashDelay = flashDelay;
}