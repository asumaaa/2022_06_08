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
	worldTransform_.translation_ = { 0,10,0 };
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
	switch (phase_)
	{
	case Phase::Approach:
	default:
		MoveApproach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}
	worldTransform_.translation_ += move;
}

void Enemy::MoveApproach()
{
	move = { speed,0,0 };
	//規定の位置に達したら離脱
	if (worldTransform_.translation_.x > 20.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	move = { 0,speed,0 };
}

void Enemy::Attack()
{
	//弾を生成し、初期化
	if (bulletTimer % 60 == 0)
	{
		Vector3 velocity(0, 0, kBulletSpeed);

		//速度ベクトルを自機の向きに併せて回転させる
		worldTransformRoll(&velocity, &worldTransform_);

		//弾を生成し初期化
		std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		//弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}
