/*
	====== LevelEditorLayer::addObjectFromVector ======
	
	Adds an object to the editor from raw object string data,
	unless it's a secret (main) coin or we are attempting to
	exceed the maximum user coin count of 3.
	
*/
GameObject* LevelEditorLayer::addObjectFromVector(std::vector<std::string>& values, std::vector<void *>& exists)
{

	auto obj = GameObject::objectFromVector(values, exists, this, false);
	if (!obj)
		return nullptr;

	int userCoin = 1329;
	int secretCoin = 142;
	int id = obj->m_objectID;

	if (id != secretCoin && (id != userCoin || m_coinCount <= 2)) {
		obj->setVisible(false);
		addToSection(obj);
		addSpecial(obj);
		return obj;
	}

	return nullptr;
}