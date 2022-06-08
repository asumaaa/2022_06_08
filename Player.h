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
#include "memory.h"
#include "list"

class Player
{

public:
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection viewProjection);
	void Update();
	void Draw();
	void Move();
	void Rotation();

	void Attack();
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	ViewProjection viewProjection_;

	float speed = 0.2;
	Vector3 move;
	float role = 0;

	//’e
	Vector3 position;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};

