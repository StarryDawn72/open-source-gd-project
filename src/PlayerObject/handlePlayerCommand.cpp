#define kPlayerCommandStopSlide 543

void PlayerObject::handlePlayerCommand(int command)
{
    if (command == kPlayerCommandStopSlide)
    {
        m_isAccelerating = false;
        m_affectedByForces = false;
    }
}
