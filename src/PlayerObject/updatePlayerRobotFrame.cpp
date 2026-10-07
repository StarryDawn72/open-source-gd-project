<<<<<<< HEAD
void PlayerObject::updatePlayerRobotFrame(int frame)
{
    createRobot(std::clamp(frame, 1, 68));
}
=======
#define kMaxRobotFrame 68

void PlayerObject::updatePlayerRobotFrame(int frame)
{
    createRobot(MIN(MAX(frame, 1), kMaxRobotFrame));
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
