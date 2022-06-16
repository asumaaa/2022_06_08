#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Transform.h"
#include "TextureManager.h"
#include <cassert>
#include "math.h"
#include "Matrix4.h"
#include "DebugText.h"
#include "Input.h"
#include "EnemyBullet.h"

class Enemy
{
public:
	void Initialize(Model* model,  ViewProjection viewProjection);
	void Update();
	void Draw();
	
	//�ړ����܂Ƃ߂��֐�
	void Move();
	//�t�F�[�Y���Ƃ̈ړ��֐�
	void MoveApproach();
	void Leave();

	//�U���̊֐�
	void Attack();
	void AttackUpdate();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//�G�̍��W�ɉ��Z����x�N�g��
	Vector3 move;
	Vector3 roll;

	//�s���t�F�[�Y
	enum class Phase
	{
		Approach,
		Leave
	};
	Phase phase_ = Phase::Approach;

	//�ړ����x
	float speed = 0.2;

	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	float kBulletSpeed = 1.5f;

	//���˃^�C�}�[
	int32_t bulletTimer = 0;

public:
	//���ˊԊu
	static const int kAttackInterval = 60;
	//�ڋ߃t�F�[�Y������
	void ApproachInitialize();
};