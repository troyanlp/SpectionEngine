#ifndef COMPONENTCAMERA_H
#define COMPONENTCAMERA_H

#include "Component.h"
class ComponentCamera :
	public Component
{
public:
	ComponentCamera(GameObject* container);
	~ComponentCamera();
};

#endif // !COMPONENTCAMERA_H