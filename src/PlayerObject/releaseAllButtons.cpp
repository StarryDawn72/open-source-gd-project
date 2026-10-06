void PlayerObject::releaseAllButtons()
{
    releaseButton(PlayerButton::Jump);
    releaseButton(PlayerButton::Left);
    releaseButton(PlayerButton::Right);
    releaseButton((PlayerButton)5);
}