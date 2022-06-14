#include "Player.h"
#define PI 3.1415

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	this->viewProjection_ = viewProjection;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
}

void Player::Update()
{
	Move();

	/*Move();*/
	/*Rotation();*/

	/*Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}*/
	worldTransformUpdate(&worldTransform_);

	worldTransform_.TransferMatrix();
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

	//�ړ����E���W
	const float kMoveLimitX = 36;
	const float kMoveLimitY = 20;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitY);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitY);

	worldTransform_.translation_ += move;
}
void Player::Rotation()
{
	if (input_->PushKey(DIK_Z))
	{
		role = { 0.0f,0.2f,0.0f };
	}
	else if (input_->PushKey(DIK_X))
	{
		role = { 0.0f,-0.2f,0.0f };
	}
	else
	{
		role = { 0.0f,0.0f,0.0f };
	}
	worldTransform_.rotation_ += role;

}

void Player::Attack()
{
	//�e�𐶐����A������
	if (input_->TriggerKey(DIK_SPACE))
	{
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		position = { worldTransform_.matWorld_.m[3][0],worldTransform_.matWorld_.m[3][1]
			,worldTransform_.matWorld_.m[3][2] };
		newBullet->Initialize(model_, position);

		//����o�^����
		bullets_.push_back(std::move(newBullet));
	}
}