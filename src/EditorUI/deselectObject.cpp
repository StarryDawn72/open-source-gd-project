/*
	Removes the given object from the selection
	in the editor.
	
*/
void EditorUI::deselectObject(GameObject *object)
{
	if ( m_selectedObject && m_selectedObject->m_uniqueID == object->m_uniqueID )
	{
		EditorUI::deselectObject();
		m_canActivateControls = true;
	}
	else
	{
		object->deselectObject();
		if (m_selectedObjects->containsObject(m_selectedObject) )
		{
			m_canActivateControls = true;
			m_selectedObjects->removeObject(object, true);
		}
	}
}
/*
	
	Deselects the currently selected object.
	
*/
void EditorUI::deselectObject()
{
    stopActionByTag(124);

    if (m_selectedObject)
        m_selectedObject->deselectObject();

    m_selectedObject = nullptr;
    toggleEditObjectButton();
    m_canActivateControls = true;
    m_lastTouchPoint = CCPointZero;
}