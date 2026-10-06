void PlayerObject::updatePlayerSpiderFrame(int frame)
{
    createSpider(std::clamp(frame, 1, 69));
}