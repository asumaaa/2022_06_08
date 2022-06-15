#include "Transform.h"
#include <cassert>
#include "math.h"

void worldTransformScale(WorldTransform* worldTransform_, float x, float y, float z)
{
	worldTransform_->scale_ = { x,y,z };
	Matrix4 matScale(
		worldTransform_->scale_.x, 0.0f, 0.0f, 0.0f,
		0.0f, worldTransform_->scale_.y, 0.0f, 0.0f,
		0.0f, 0.0f, worldTransform_->scale_.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	worldTransform_->matWorld_ *= matScale;
}

void worldTransformMove(WorldTransform* worldTransform_, float x, float y, float z)
{
	worldTransform_->translation_ = { x,y,z };
	Matrix4 matTrans(
		1.0f, 0.0f, 0.0f, 0,
		0.0f, 1.0f, 0.0f, 0,
		0.0f, 0.0f, 1.0f, 0,
		worldTransform_->translation_.x, worldTransform_->translation_.y, worldTransform_->translation_.z, 1.0f
	);
	worldTransform_->matWorld_ *= matTrans;
}

void worldTransformRole(WorldTransform* worldTransform_, float x, float y, float z)
{
	worldTransform_->rotation_ = { x,y,z };
	Matrix4 matRot;
	Matrix4 matRotX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(worldTransform_->rotation_.x), sin(worldTransform_->rotation_.x), 0.0f,
		0.0f, -sin(worldTransform_->rotation_.x), cos(worldTransform_->rotation_.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	Matrix4 matRotY(
		cos(worldTransform_->rotation_.y), 0.0f, -sin(worldTransform_->rotation_.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin(worldTransform_->rotation_.y), 0.0f, cos(worldTransform_->rotation_.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	Matrix4 matRotZ(
		cos(worldTransform_->rotation_.z), sin(worldTransform_->rotation_.z), 0.0f, 0.0f,
		-sin(worldTransform_->rotation_.z), cos(worldTransform_->rotation_.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	matRot = matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;
	worldTransform_->matWorld_ *= matRot;
}

void worldTransformScaleSet(WorldTransform* worldTransform_, float x, float y, float z)
{
	worldTransform_->matWorld_.m[0][0] = x;
	worldTransform_->matWorld_.m[0][1] = y;
	worldTransform_->matWorld_.m[0][2] = z;
}

void worldTransformTransrationSet(WorldTransform* worldTransform_, float x, float y, float z)
{
	worldTransform_->matWorld_.m[3][0] = x;
	worldTransform_->matWorld_.m[3][1] = y;
	worldTransform_->matWorld_.m[3][2] = z;
}

void worldTransformRoleSet(WorldTransform* worldTransform_, float x, float y, float z)
{
	worldTransform_->rotation_ = { x,y,z };
}

void worldTransformUpdate(WorldTransform* worldTransform_)
{
	worldTransform_->matWorld_ = {
		worldTransform_->scale_.x, 0.0f, 0.0f, 0.0f,
		0.0f, worldTransform_->scale_.y, 0.0f, 0.0f,
		0.0f, 0.0f, worldTransform_->scale_.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Matrix4 matTrans(
		1.0f, 0.0f, 0.0f, 0,
		0.0f, 1.0f, 0.0f, 0,
		0.0f, 0.0f, 1.0f, 0,
		worldTransform_->translation_.x, worldTransform_->translation_.y, worldTransform_->translation_.z, 1.0f
	);
	Matrix4 matRotX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(worldTransform_->rotation_.x), sin(worldTransform_->rotation_.x), 0.0f,
		0.0f, -sin(worldTransform_->rotation_.x), cos(worldTransform_->rotation_.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	Matrix4 matRotY(
		cos(worldTransform_->rotation_.y), 0.0f, -sin(worldTransform_->rotation_.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin(worldTransform_->rotation_.y), 0.0f, cos(worldTransform_->rotation_.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	Matrix4 matRotZ(
		cos(worldTransform_->rotation_.z), sin(worldTransform_->rotation_.z), 0.0f, 0.0f,
		-sin(worldTransform_->rotation_.z), cos(worldTransform_->rotation_.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	worldTransform_->matWorld_ *= matRotZ;
	worldTransform_->matWorld_ *= matRotX;
	worldTransform_->matWorld_ *= matRotY;
	worldTransform_->matWorld_ *= matTrans;

	worldTransform_->TransferMatrix();
}