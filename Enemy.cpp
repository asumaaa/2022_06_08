#include "Enemy.h"

void Enemy::Initialize(Model* model,  ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->viewProjection_ = viewProjection;

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("purple.png");

	//ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 10,10,0 };

	//フェーズ初期化
	ApproachInitialize();
}

void Enemy::Update()
{
	Move();
	worldTransformUpdate(&worldTransform_);

	AttackUpdate();
}

void Enemy::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
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

	roll = { 0,0.02f,0 };
	worldTransform_.translation_ += move;
	worldTransform_.rotation_ += roll;
}

void Enemy::MoveApproach()
{
	bulletTimer--;
	//一定間隔で弾を発射
	if (bulletTimer == 0)
	{
		Attack();
		bulletTimer = kAttackInterval;
	}
	move = { 0,0,speed };
	//規定の位置に達したら離脱
	if (worldTransform_.translation_.z >= 20.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	move = { 0,0,-speed };
	//規定の位置に達したら離脱
	if (worldTransform_.translation_.z <= -20.0f)
	{
		phase_ = Phase::Approach;
	}
}

void Enemy::Attack()
{
	assert(player_);

	Vector3 velocity(0, 0, kBulletSpeed);

	//速度ベクトルを自機の向きに併せて回転させる
	worldTransformRoll(&velocity, &worldTransform_);

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Enemy::AttackUpdate()
{
	//弾更新
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		});
}

void Enemy::ApproachInitialize()
{
	bulletTimer = kAttackInterval;
}
