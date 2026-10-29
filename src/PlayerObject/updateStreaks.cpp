// @version 2.2081
void PlayerObject::updateStreaks(float dt)
{
    if (m_shipStreak) m_shipStreak->update(dt);
}