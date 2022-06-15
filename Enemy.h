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
#include "EnemyBullet.h"

class Enemy
{
public:
	void Initialize(Model* model,  ViewProjection viewProjection);
	void Update();
	void Draw();
	
	//移動をまとめた関数
	void Move();
	//フェーズごとの移動関数
	void MoveApproach();
	void Leave();

	//攻撃の関数
	void Attack();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ViewProjection viewProjection_;

	//敵の座標に加算するベクトル
	Vector3 move;

	//行動フェーズ
	enum class Phase
	{
		Approach,
		Leave
	};
	Phase phase_ = Phase::Approach;

	//移動速度
	float speed = 0.2;

	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	float kBulletSpeed = 1.0f;
	float bulletTimer = 0;
};