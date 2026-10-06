void PlayerObject::updatePlayerRobotFrame(int frame)
{
    createRobot(std::clamp(frame, 1, 68));
}