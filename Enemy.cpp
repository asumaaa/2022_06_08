#include "Enemy.h"

void Enemy::Initialize(Model* model,  ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->viewProjection_ = viewProjection;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("purple.png");

	//���[���h�g�����X�t�H�[��������
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
	if (worldTransform_.translation_.x <= -36)
	{
		speed = -speed;
	}
	if (worldTransform_.translation_.x >= 36)
	{
		speed = -speed;
	}
	Vector3 Move = { speed,0,0 };
	worldTransform_.translation_ += Move;
}
