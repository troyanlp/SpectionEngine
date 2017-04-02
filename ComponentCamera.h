#ifndef COMPONENTCAMERA_H
#define COMPONENTCAMERA_H

#include "Component.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "MemLeaks.h"

enum Axis {
	X,
	Y,
	Z
};

class ComponentCamera :
	public Component
{
public:
	friend class ModuleCamera;
	ComponentCamera(GameObject* container, std::string id);
	~ComponentCamera();

	//Projection Related Functions
	void ChangeWindowSize(int width, int height);
	void SetFOV(float verticalFov);
	void SetAspectRatio(float aspectRatio);
	void SetPlaneDistances(float near, float far);

	
	void SetPosition(const math::vec &pos);
	/**
	Sets the camera Up vector and Front vector
	@param up The up vector
	@param front The front vector
	*/
	void SetLookAt(const math::vec &up, const math::vec &front);

	float * GetMatrixProjection() const;
	float * GetMatrixView() const;
	void Update(float dt);

	void SetMouseBlocked(bool mouseBlocked);
	void DrawFrustum();

	bool ContainsAaBox(const math::AABB & refBox) const;

	bool DrawGUI();

	bool IsFrustumCulling();

private:
	void Traslate(const float3 &movement, const float angleX, const float angleY);

public:
	//These two params may be added as json config
	float movementSpeed = 0;
	float rotationSpeed = 0;

	bool invertXAxis = false;
	bool invertYAxis = false;


private:
	Frustum frustum;
	float aspectRatio = 1.78;
	float verticalFov = 30;
	float horizontalFov = 30;
	float nearPlane = 0;
	float farPlane = 0;

	math::vec pos = { 0,0,0 };

	bool mouseBlocked = false;
	bool active = false;
	bool frustumCulling = false;
};

#endif // !COMPONENTCAMERA_H