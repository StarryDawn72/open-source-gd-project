void PlayerObject::releaseAllButtons()
{
    releaseButton(PlayerButton::Jump);
    releaseButton(PlayerButton::Left);
    releaseButton(PlayerButton::Right);
    releaseButton((PlayerButton)5); // Unknown/unused, might have also been an enum value
}
