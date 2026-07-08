/*
	====== PLAYEROBJECT::SETYVELOCITY ======
	
	This function sets the current player's vertical velocity
	with a rounding to the third decimal place. The second parameter is
	unused and its real name is unknown.
	
*/
void PlayerObject::setYVelocity(double velocity, int type)
{
   double intPart = (int)velocity;

   if (velocity == intPart) {
      m_yVelocity = velocity;
      return;
   }

   m_yVelocity = (double)std::round((velocity - intPart) * 1000.0) / 1000.0 + intPart;
}