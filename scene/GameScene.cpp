#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "math.h"
#include "Matrix4.h"
#include <random>
#include <DirectXMath.h>
using namespace DirectX;

#define PI 3.1415

GameScene::GameScene() {}

GameScene::~GameScene()
{
	/*for (int i = 0; i < 7; i++)
	{
		delete player_[i];
	}*/
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Mario.jpg");

	//3Dモデルの生成
	model_ = Model::Create();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//ビュープロジェクション
	viewProjection_.Initialize();

	//初期化
	for (int i = 0; i < 9; i++)
	{
		worldTransforms_[i].Initialize();
	}

	//脊椎
	worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
	worldTransforms_[PartId::kSpine].translation_ = {0,4.5f,0};

	//上半身
	//胸
	worldTransforms_[PartId::kChest].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kChest].translation_ = { 0,4.5f,0 };
	//頭
	worldTransforms_[PartId::kHead].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kHead].translation_ = { 0,4.5f,0 };
	//左腕
	worldTransforms_[PartId::kArmL].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmL].translation_ = { 4.5f,0,0 };
	//右腕
	worldTransforms_[PartId::kArmR].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmR].translation_ = { -4.5f,0,0 };

	//下半身
	//尻
	worldTransforms_[PartId::kHip].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kHip].translation_ = { 0,0,0 };
	//左足
	worldTransforms_[PartId::kLegL].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegL].translation_ = { 4.5f,-4.5f,0 };
	//右足
	worldTransforms_[PartId::kLegR].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegR].translation_ = { -4.5f,-4.5f,0 };

}

void GameScene::Update()
{
	Vector3 move = { 0,0,0 };
	Vector3 roleU = { 0,0,0 };
	Vector3 roleD = { 0,0,0 };

	if (input_->PushKey(DIK_A))
	{
		move = { -0.2f,0.0f,0.0f };
	}
	else if (input_->PushKey(DIK_D))
	{
		move = { 0.2f,0.0f,0.0f };
	}
	else if (input_->PushKey(DIK_W))
	{
		move = { 0.0f,0.2f,0.0f };
	}
	else if (input_->PushKey(DIK_S))
	{
		move = { 0.0f,-0.2f,0.0f };
	}
	else
	{
		move = { 0.0f,0.0f,0.0f };
	}

	if (input_->PushKey(DIK_U))
	{
		roleU = { 0.0f,0.02f,0.0f };
	}
	else if (input_->PushKey(DIK_I))
	{
		roleU = { 0.0f,-0.02f,0.0f };
	}
	else
	{
		roleU = { 0.0f,0.0f,0.0f };
	}

	if (input_->PushKey(DIK_J))
	{
		roleD = { 0.0f,0.02f,0.0f };
	}
	else if (input_->PushKey(DIK_K))
	{
		roleD = { 0.0f,-0.02f,0.0f };
	}
	else
	{
		roleD = { 0.0f,0.0f,0.0f };
	}

	worldTransforms_[kRoot].translation_ += move;
	worldTransformUpdate(&worldTransforms_[0]);
	worldTransforms_[0].TransferMatrix();

	worldTransforms_[kChest].rotation_ += roleU;
	worldTransforms_[kHip].rotation_ += roleD;

	for (int i = 1; i < 9; i++)
	{
		worldTransformUpdate(&worldTransforms_[i]);
		worldTransforms_[i].matWorld_ *= worldTransforms_[i].parent_->matWorld_;
		worldTransforms_[i].TransferMatrix();
	}

	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//3Dモデル描画
	//自キャラの描画
	for (int i = 2; i < 9; i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
