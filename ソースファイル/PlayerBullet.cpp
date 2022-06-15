#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	//ワールド座標初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	/*worldTransformScale(&worldTransform_, scale.x, scale.y, scale.z);
	worldTransformTransrationSet(&worldTransform_, worldTransform_.translation_.x, worldTransform_.translation_.y,
		worldTransform_.translation_.z);
	worldTransformRole(&worldTransform_, rotation.x, rotation.y, rotation.z);*/

	worldTransformUpdate(&worldTransform_);

}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
