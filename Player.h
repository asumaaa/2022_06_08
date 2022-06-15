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
#include "PlayerBullet.h"
#include "memory"
#include "list"

class Player
{

public:
	void Initialize(Model* model,  ViewProjection viewProjection);
	void Update();
	void Draw();

	//à⁄ìÆ
	void Move();
	//âÒì]
	void Rotation();

	//çUåÇ
	void Attack();
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ViewProjection viewProjection_;

	//à⁄ìÆ
	float speed = 0.2;
	Vector3 move;
	//âÒì]
	float rollSpeed = 0.02;
	Vector3 roll;

	//íe
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	float kBulletSpeed = 1.0f;
};

