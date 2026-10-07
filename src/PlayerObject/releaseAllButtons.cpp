void PlayerObject::releaseAllButtons()
{
    releaseButton(PlayerButton::Jump);
    releaseButton(PlayerButton::Left);
    releaseButton(PlayerButton::Right);
<<<<<<< HEAD
    releaseButton((PlayerButton)5);
}
=======
    releaseButton((PlayerButton)5); // Unknown/unused, might have also been an enum value
}
>>>>>>> c9db2f7f95e7706561b3d060def884ae514c1342
