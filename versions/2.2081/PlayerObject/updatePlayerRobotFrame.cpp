void PlayerObject::updatePlayerRobotFrame(int frame)
{
    createRobot(MIN(MAX(frame, 1), kMaxRobotFrame));
}
