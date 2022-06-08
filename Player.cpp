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

	//ワールド変換初期化
	worldTransform_.Initialize();
}

void Player::Update()
{
	Move();
	Rotation();

	Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 150);
	debugText_->Printf("%f.%f.%f", worldTransform_.matWorld_.m[0][2],
		worldTransform_.matWorld_.m[2][2], worldTransform_.matWorld_.m[1][2]);
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
		move = { -speed,0,0 };
	}
	else if (input_->PushKey(DIK_D))
	{
		move = { speed,0,0 };
	}
	else if (input_->PushKey(DIK_W))
	{
		move = { 0,speed,0 };
	}
	else if (input_->PushKey(DIK_S))
	{
		move = { 0,-speed,0 };
	}
	else
	{
		move = { 0,0,0 };
	}

	//移動限界座標
	const float kMoveLimitX = 36;
	const float kMoveLimitY = 20;

	worldTransform_.matWorld_.m[3][0] = max(worldTransform_.matWorld_.m[3][0], -kMoveLimitX);
	worldTransform_.matWorld_.m[3][0] = min(worldTransform_.matWorld_.m[3][0], +kMoveLimitX);
	worldTransform_.matWorld_.m[3][1] = max(worldTransform_.matWorld_.m[3][1], -kMoveLimitY);
	worldTransform_.matWorld_.m[3][1] = min(worldTransform_.matWorld_.m[3][1], +kMoveLimitY);

	debugText_->SetPos(50, 150);
	worldTransformMove(&worldTransform_, move.x, move.y, move.z);
}

void Player::Rotation()
{
	if (input_->PushKey(DIK_Z))
	{
		role = 0.02;
	}
	else if (input_->PushKey(DIK_X))
	{
		role = -0.02;
	}
	else
	{
		role = 0;
	}
	worldTransformRole(&worldTransform_, 0, role, 0);

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
