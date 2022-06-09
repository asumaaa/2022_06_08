#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Transform.h"
#include "TextureManager.h"
#include <cassert>
#include "math.h"
#include "Matrix4.h"
#include "DebugText.h"
#include "Input.h"

class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	/*Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;*/
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	Vector3 move = { 0,0,0 };
	Vector3 rotation = { 0,0,0 };
	Vector3 scale = { 1,1,1 };

	Vector3 velocity_;

};

