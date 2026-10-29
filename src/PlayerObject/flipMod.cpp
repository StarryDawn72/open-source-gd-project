// @version 2.2081
/*
	Returns the gravity direction as an integer.
*/
int PlayerObject::flipMod()
{
	return m_isUpsideDown ? -1 : 1;
}