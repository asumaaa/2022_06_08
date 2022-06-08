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
	for (int i = 0; i < 100; i++)
	{
		delete player_[i];
	}
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

	//カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = XMConvertToRadians(10.0f);
	//ビュープロジェクション
	viewProjection_.Initialize();

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_real_distribution<float>xTransRange(-10, 10);
	std::uniform_real_distribution<float>yTransRange(-10, 10);
	std::uniform_real_distribution<float>zTransRange(-10, 10);
	std::uniform_real_distribution<float>xRotateRange(0, 2*PI);
	std::uniform_real_distribution<float>yRotateRange(0, 2*PI);
	std::uniform_real_distribution<float>zRotateRange(0, 2*PI);

	//自キャラの生成
	for (int i = 0; i < 100; i++)
	{
		player_[i] = new Player();
	}

	//自キャラの初期化
	for (int i = 0; i < 100; i++)
	{
		worldTransforms_[i].Initialize();
		worldTransforms_[i].translation_ = { xTransRange(engine),yTransRange(engine) ,zTransRange(engine) };
		worldTransforms_[i].rotation_ = { xRotateRange(engine),yRotateRange(engine) ,zRotateRange(engine) };

		player_[i]->Initialize(model_, textureHandle_, viewProjection_, worldTransforms_[i]);
	}
}

void GameScene::Update()
{
	//if (input_->PushKey(DIK_W))
	//{
	//	moveEye = { 0,0,kEyeSpeed };
	//}
	//else if (input_->PushKey(DIK_S))
	//{
	//	moveEye = { 0,0,-kEyeSpeed };
	//}
	//else
	//{
	//	moveEye = { 0,0,0 };
	//}

	//if (input_->PushKey(DIK_LEFT))
	//{
	//	moveTraget = { -kTragetSpeed,0,0 };
	//}
	//else if (input_->PushKey(DIK_RIGHT))
	//{
	//	moveTraget = { kTragetSpeed,0,0 };
	//}
	//else
	//{
	//	moveTraget = { 0,0,0 };
	//}

	//if (input_->PushKey(DIK_SPACE))
	//{
	//	viewAngle += kUpRotSpeed;
	//	//2πを超えたら0に戻す
	//	viewAngle = fmodf(viewAngle, PI * 2.0f);
	//}

	////視点移動（ベクトルの加算）
	//viewProjection_.eye += moveEye;
	//viewProjection_.target += moveTraget;
	//viewProjection_.up = { cosf(viewAngle),sinf(viewAngle),0.0f };

	//上キーで視野角が広がる
	if (input_->PushKey(DIK_UP))
	{
		viewProjection_.fovAngleY += 0.1;
	}

	//行列の再計算
	viewProjection_.UpdateMatrix();

	//自キャラの更新
	for (int i = 0; i < 100; i++)
	{
		player_[i]->Update();
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
	for (int i = 0; i < 100; i++)
	{
		player_[i]->Draw();
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
