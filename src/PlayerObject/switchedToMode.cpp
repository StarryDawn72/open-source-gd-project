// UNTESTED
void PlayerObject::switchedToMode(GameObjectType type) {
    if (type != GameObjectType::ShipPortal)
        toggleFlyMode(false, false);
    if (type != GameObjectType::UfoPortal)
        toggleBirdMode(false, false);
    if (type != GameObjectType::BallPortal)
        toggleRollMode(false, false);
    if (type != GameObjectType::WavePortal)
        toggleDartMode(false, false);
    if (type != GameObjectType::RobotPortal)
        toggleRobotMode(false, false);
    if (type != GameObjectType::SpiderPortal)
        toggleSpiderMode(false, false);
    if (type != GameObjectType::SwingPortal)
        toggleSwingMode(false, false);
}