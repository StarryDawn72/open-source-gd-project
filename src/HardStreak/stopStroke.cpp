// @version 2.2081
void HardStreak::stopStroke()
{
    unschedule(schedule_selector(HardStreak::updateStroke));
    m_drawStreak = false;
    reset();
}