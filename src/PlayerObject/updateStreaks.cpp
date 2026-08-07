void PlayerObject::updateStreaks(float dt)
{
    if (m_shipStreak) m_shipStreak->update(dt);
}