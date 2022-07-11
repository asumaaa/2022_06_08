﻿#include "GameScene.h"
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
	for (int i = 0; i < 5; i++)
	{
		delete player_[i];
	}
	/*delete enemy_;*/
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//3Dモデルの生成
	model_ = Model::Create();

	//乱数シェード生成
	std::random_device seed_gen;
	//メルセンヌツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲
	std::uniform_real_distribution<float>posDist(-20.0f, 20.0f);

	//初期化
	for (int i = 0; i < 5; i++)
	{
		player_[i] = new Player();
		player_[i]->Initialize(model_);
		player_[i]->worldTransform_.translation_ = { posDist(engine),posDist(engine),0};
	}
}

void GameScene::Update()
{
	//スペースキーを押すごとに注視点を変更
	if (input_->TriggerKey(DIK_SPACE))
	{
		if (viewNum != 4)
		{
			viewNum++;
		}
		else
		{
			viewNum = 0;
		}
	}
	//注視点変更
	viewProjection_.target = { player_[viewNum]->worldTransform_.translation_.x,player_[viewNum]->worldTransform_.translation_.y,
	player_[viewNum]->worldTransform_.translation_.z };
	//ビュー座標をオブジェクトの目の前に
	viewProjection_.eye = { player_[viewNum]->worldTransform_.translation_.x,player_[viewNum]->worldTransform_.translation_.y,-50 };

	viewProjection_.Initialize();

	for (int i = 0; i < 5; i++)
	{
		player_[i]->Update(viewProjection_);
	}
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
	for (int i = 0; i < 5; i++)
	{
		player_[i]->Draw();
	}
	//enemy_->Draw();

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
