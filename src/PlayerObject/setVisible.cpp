void PlayerObject::setVisible(bool visible)
{
	if (m_isHidden)visible = false;
	GameObject::setVisible(visible);
}