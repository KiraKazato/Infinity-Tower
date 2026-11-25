#pragma once
#include "DxLib.h"

class Game
{
public:
	Game();
	~Game();

	//外部から呼ぶゲームのループ関数
	void Run();

private:
	//ゲームの初期化
	bool Initialize();
	//ゲームの更新
	void Update();
	//ゲームの描画
	void Draw();

private:
	//ゲームループさせるフラグ
	bool mbRunning = false;
	//画面のサイズ
	int mnWindowWidth = 1920;
	int mnWindowHeight = 1080;
};