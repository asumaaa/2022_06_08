#include "Player.h"
#define PI 3.1415

void Player::Initialize(Model* model, ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->viewProjection_ = viewProjection;

	textureHandle_ = TextureManager::Load("Mario.jpg");

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�g�����X�t�H�[��������
	worldTransform_.Initialize();
}

void Player::Update()
{

	Move();
	Rotation();

	Attack();

	worldTransformUpdate(&worldTransform_);

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

	//�ړ����E���W
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
		roll = { 0.0f,-rollSpeed,0.0f };
	}
	else if (input_->PushKey(DIK_X))
	{
		roll = { 0.0f,rollSpeed,0.0f };
	}
	else
	{
		roll = { 0.0f,0.0f,0.0f };
	}
	worldTransform_.rotation_ += roll;

}

void Player::Attack()
{
	//�e�𐶐����A������
	if (input_->TriggerKey(DIK_SPACE))
	{
		Vector3 velocity(0, 0, kBulletSpeed);

		//���x�x�N�g�������@�̌����ɕ����ĉ�]������
		worldTransformRoll(&velocity, &worldTransform_);

		//�e�𐶐���������
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));
	}

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet)
		{
			return bullet->IsDead();
		});
}