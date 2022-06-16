#include "Enemy.h"

void Enemy::Initialize(Model* model,  ViewProjection viewProjection)
{
	assert(model);
	this->model_ = model;
	this->viewProjection_ = viewProjection;

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("purple.png");

	//���[���h�g�����X�t�H�[��������
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 10,10,0 };

	//�t�F�[�Y������
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
	//���Ԋu�Œe�𔭎�
	if (bulletTimer == 0)
	{
		Attack();
		bulletTimer = kAttackInterval;
	}
	move = { 0,0,speed };
	//�K��̈ʒu�ɒB�����痣�E
	if (worldTransform_.translation_.z >= 20.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	move = { 0,0,-speed };
	//�K��̈ʒu�ɒB�����痣�E
	if (worldTransform_.translation_.z <= -20.0f)
	{
		phase_ = Phase::Approach;
	}
}

void Enemy::Attack()
{
	assert(player_);

	Vector3 velocity(0, 0, kBulletSpeed);

	//���x�x�N�g�������@�̌����ɕ����ĉ�]������
	worldTransformRoll(&velocity, &worldTransform_);

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Enemy::AttackUpdate()
{
	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		});
}

void Enemy::ApproachInitialize()
{
	bulletTimer = kAttackInterval;
}
