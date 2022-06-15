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
	//�K��̈ʒu�ɒB�����痣�E
	if (worldTransform_.translation_.x > 20.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	move = { 0,speed,0 };
}
