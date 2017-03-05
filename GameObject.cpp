#include "GameObject.h"
#include "Component.h"
#include "Globals.h"
#include "ComponentCamera.h"
#include "ComponentLight.h"
#include "ComponentMaterial.h"
#include "ComponentModel.h"
#include "ComponentScript.h"
#include "ComponentTransform.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
	for (std::list<GameObject *>::iterator it = childrens.begin(); it != childrens.end();) {
		delete (*it);
		it = childrens.erase(it);
		++it;
	}

	for (std::list<Component *>::iterator it = components.begin(); it != components.end();) {
		delete (*it);
		it = components.erase(it);
		++it;
	}
}

Component * GameObject::addComponent(const ComponentType &type)
{
	Component *result = nullptr;
	int typeCounter = componentCounter[type];

	//If typeCounter is zero it means that can add any number components of this type
	if (typeCounter > 0 && typeCounter < result->maxNumberOfComponentByGameObject) {
		return result;
	}
	switch (type) {
	case ComponentType::COMPONENT_TYPE_CAMERA:
		result = new ComponentCamera();
		break;
	case ComponentType::COMPONENT_TYPE_LIGHT:	
			result = new ComponentLight();
		break;
	case ComponentType::COMPONENT_TYPE_MATERIAL:
		result = new ComponentMaterial();
		break;
	case ComponentType::COMPONENT_TYPE_MODEL:
		result = new ComponentModel();
		break;
	case ComponentType::COMPONENT_TYPE_SCRIPT:
		result = new ComponentScript();
		break;
	case ComponentType::COMPONENT_TYPE_TRANSFORM:
		result = new ComponentTransform();
		break;
	}

	if (result != nullptr) {
		++componentCounter[type];
		components.push_back(result);
	}

	return result;
}

bool GameObject::removeComponent(Component *component)
{
	bool found = false;
	//Find Component
	for (std::list<Component *>::iterator it = components.begin(); it != components.end();) {
		if (component == (*it)) {
			--componentCounter[(*it)->type];
			RELEASE(*it);
			components.erase(it);
			found = true;
			break;
		}
		else {
			++it;
		}
	}
	
	return found;
	
}

void GameObject::Update()
{
}

