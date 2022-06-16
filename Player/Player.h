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

	//移動
	void Move();
	//回転
	void Rotation();

	//攻撃
	void Attack();

	//ワールドトランスフォームを取得
	WorldTransform GetWorldtransform() { return worldTransform_; }
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ViewProjection viewProjection_;

	//移動
	float speed = 0.2;
	Vector3 move;
	//回転
	float rollSpeed = 0.02;
	Vector3 roll;

	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	float kBulletSpeed = 1.0f;
};

