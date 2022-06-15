#include "Enemy.h"

void Enemy::Initialize(Model* model,  ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->viewProjection_ = viewProjection;

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("purple.png");

	//ワールドトランスフォーム初期化
	worldTransform_.Initialize();
}

void Enemy::Update()
{
	Move();
	worldTransformUpdate(&worldTransform_);
}

void Enemy::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

void Enemy::Move()
{
	Vector3 Move(0,speed,0);
	worldTransform_.translation_ += Move;
}
