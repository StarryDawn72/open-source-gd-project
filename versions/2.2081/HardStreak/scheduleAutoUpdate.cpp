void HardStreak::scheduleAutoUpdate()
{
    schedule(schedule_selector(HardStreak::updateStroke), 0);
}