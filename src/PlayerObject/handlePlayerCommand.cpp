<<<<<<< HEAD
=======
#define kPlayerCommandStopSlide 543

>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
void PlayerObject::handlePlayerCommand(int command)
{
    if (command == kPlayerCommandStopSlide)
    {
        m_isAccelerating = false;
        m_affectedByForces = false;
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
