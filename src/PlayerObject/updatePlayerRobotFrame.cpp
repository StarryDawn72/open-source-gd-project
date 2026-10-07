#define kMaxRobotFrame 68

void PlayerObject::updatePlayerRobotFrame(int frame)
{
    createRobot(MIN(MAX(frame, 1), kMaxRobotFrame));
}
