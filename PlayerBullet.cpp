#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_ = model;
	velocity_ = velocity;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	//ワールド座標初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransformTransrationSet(&worldTransform_, position.x, position.y, position.z);
}

void PlayerBullet::Update()
{
	worldTransform_.translation_ += velocity_;
	/*worldTransformScale(&worldTransform_, scale.x, scale.y, scale.z);
	worldTransformTransrationSet(&worldTransform_, worldTransform_.translation_.x, worldTransform_.translation_.y,
		worldTransform_.translation_.z);
	worldTransformRole(&worldTransform_, rotation.x, rotation.y, rotation.z);*/

	worldTransform_.TransferMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
