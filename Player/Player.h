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
#include "PlayerBullet.h"
#include "memory"
#include "list"

class Player
{

public:
	void Initialize(Model* model,  ViewProjection viewProjection);
	void Update();
	void Draw();

	//�ړ�
	void Move();
	//��]
	void Rotation();

	//�U��
	void Attack();

	//���[���h�g�����X�t�H�[�����擾
	WorldTransform GetWorldtransform() { return worldTransform_; }
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ViewProjection viewProjection_;

	//�ړ�
	float speed = 0.2;
	//��]
	float rollSpeed = 0.02;
	Vector3 roll;

	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	float kBulletSpeed = 1.0f;

public:
	//�e�I�u�W�F�N�g
	Player* parent = nullptr;
	WorldTransform worldTransform_;
	Vector3 move;
};

