#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_ = model;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	//���[���h���W������
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	//���W���ړ�������
	worldTransform_.translation_ += velocity_;
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}

	//�X�V
	worldTransformUpdate(&worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
