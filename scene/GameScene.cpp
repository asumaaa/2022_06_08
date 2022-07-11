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
	for (int i = 0; i < 10; i++)
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

	//ビュープロジェクション
	viewProjection_.Initialize();

	//初期化
	for (int i = 0; i < 10; i++)
	{
		player_[i] = new Player();
		player_[i]->Initialize(model_, viewProjection_);
	}
	
	float addAngle = 0.2 * PI;

	//角度をずらす
	for (int i = 0; i < 10; i++)
	{
		addMove[i] = { i * addAngle,i * addAngle,0.0f };
	}
}

void GameScene::Update()
{
	for (int i = 0; i < 10; i++)
	{
		addMove[i].x += 0.02;
		addMove[i].y += 0.02;
		player_[i]->worldTransform_.translation_ = {cos(addMove[i].x) * 10, sin(addMove[i].y) * 10,0};
	}
	for (int i = 0; i < 10; i++)
	{
		player_[i]->Update();
	}
	/*enemy_->Update();*/
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
	for (int i = 0; i < 10; i++)
	{
		player_[i]->Draw();
	}
	/*enemy_->Draw();*/

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
