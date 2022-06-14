#include "Player.h"
#define PI 3.1415

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	this->viewProjection_ = viewProjection;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
}

void Player::Update()
{

	Move();
	Rotation();

	/*Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}*/
	worldTransformUpdate(&worldTransform_);

	/*worldTransform_.TransferMatrix();*/

	debugText_->SetPos(50, 150);
	debugText_->Printf("%f.%f", worldTransform_.translation_.x,
		worldTransform_.translation_.y);
}

void Player::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}

}

void Player::Move()
{
	if (input_->PushKey(DIK_A))
	{
		move = {-speed,0.0f,0.0f};
	}
	else if (input_->PushKey(DIK_D))
	{
		move = { speed,0.0f,0.0f };
	}
	else if (input_->PushKey(DIK_W))
	{
		move = { 0.0f,speed,0.0f };
	}
	else if (input_->PushKey(DIK_S))
	{
		move = { 0.0f,-speed,0.0f };
	}
	else
	{
		move = { 0.0f,0.0f,0.0f };
	}

	//移動限界座標
	const float kMoveLimitX = 36;
	const float kMoveLimitY = 20;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_ += move;
}
void Player::Rotation()
{
	if (input_->PushKey(DIK_Z))
	{
		roll = { 0.0f,rollSpeed,0.0f };
	}
	else if (input_->PushKey(DIK_X))
	{
		roll = { 0.0f,-rollSpeed,0.0f };
	}
	else
	{
		roll = { 0.0f,0.0f,0.0f };
	}
	worldTransform_.rotation_ += roll;

}

void Player::Attack()
{
	//弾を生成し、初期化
	if (input_->TriggerKey(DIK_SPACE))
	{
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		position = { worldTransform_.matWorld_.m[3][0],worldTransform_.matWorld_.m[3][1]
			,worldTransform_.matWorld_.m[3][2] };
		newBullet->Initialize(model_, position);

		//球を登録する
		bullets_.push_back(std::move(newBullet));
	}
}
