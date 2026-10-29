// @version 2.2081
OBB2D* PlayerObject::getOrientedBox()
{
	updateOrientedBox();
	return m_orientedBox;
}