#ifndef _Camera_H_
#define _Camera_H_

#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
  void TranslateAndRender(float translation_forward, float translation_sideways);
	void GetViewMatrix(XMFLOAT4X4&);
  void SetLookAt(float lookAt);
private:
	float positionX_, positionY_, positionZ_;
	float rotationX_, rotationY_, rotationZ_;
  float lookAt_ = 1.0f;
	XMFLOAT4X4 viewmatrix_;
};

#endif