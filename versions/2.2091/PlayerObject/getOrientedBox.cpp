OBB2D* PlayerObject::getOrientedBox()
{
	updateOrientedBox();
	return m_orientedBox;
}