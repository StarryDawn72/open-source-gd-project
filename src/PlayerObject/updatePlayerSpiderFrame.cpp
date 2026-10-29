// @version 2.2081
void PlayerObject::updatePlayerSpiderFrame(int frame)
{
    createSpider(std::clamp(frame, 1, 69));
}