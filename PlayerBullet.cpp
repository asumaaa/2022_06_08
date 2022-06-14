#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_ = model;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	//ワールド座標初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	//座標を移動させる
	worldTransform_.translation_ += velocity_;
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}

	//更新
	worldTransformUpdate(&worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
