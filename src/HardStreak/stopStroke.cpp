void HardStreak::stopStroke()
{
    unschedule(schedule_selector(HardStreak::updateStroke));
    m_drawStreak = false;
    reset();
}