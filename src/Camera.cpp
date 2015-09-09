#include "../include/Camera.h"
#include <iostream>

Camera::Camera()
{
	positionX_ = 0.0f;
	positionY_ = 0.0f;
	positionZ_ = 0.0f;

	rotationX_ = 0.0f;
	rotationY_ = 0.0f;
	rotationZ_ = 0.0f;
}


Camera::Camera(const Camera& other)
{}

Camera::Camera(float x, float y, float z, float rotationX, float rotationY, float rotationZ)
{
  positionX_ = x;
  positionY_ = y;
  positionZ_ = z;
  rotationX_ = rotationX;
  rotationY_ = rotationY;
  rotationZ_ = rotationZ;
}

Camera::~Camera()
{}


void Camera::SetPosition(float x, float y, float z)
{
	positionX_ = x;
	positionY_ = y;
	positionZ_ = z;
}


void Camera::SetRotation(float rotationX, float rotationY, float rotationZ)
{
  rotationX_ = rotationX;
  rotationY_ = rotationY;
  rotationZ_ = rotationZ;
}

XMFLOAT3 Camera::GetPosition()
{
	return XMFLOAT3(positionX_, positionY_, positionZ_);
}


XMFLOAT3 Camera::GetRotation()
{
	return XMFLOAT3(rotationX_, rotationY_, rotationZ_);
}

void Camera::Render()
{
	// XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	XMVECTOR up = XMVectorSet(0.0, 1.0, 0.0, 1.0);
	// Setup the position of the camera in the world.
	XMVECTOR position = XMVectorSet(positionX_, positionY_, positionZ_, 1.0f);
	// Setup where the camera is looking by default.
	XMVECTOR lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = rotationX_ * 0.0174532925f;
	yaw = rotationY_ * 0.0174532925f;
	roll = rotationZ_ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	XMMATRIX viewMatrix_XmMat = XMMatrixLookAtLH(position, lookAt, up);
	XMStoreFloat4x4(&viewmatrix_, viewMatrix_XmMat);

	return;
}

void Camera::GetViewMatrix(XMFLOAT4X4& viewMatrix)
{
	viewMatrix = viewmatrix_;
}