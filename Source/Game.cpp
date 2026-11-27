#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
    //ＤＸライブラリ使用の終了処理
    DxLib_End();       
}

void Game::Run()
{
    //初期化に失敗したら終了
    if (!Initialize())
    {
        return;
    }

    //フラグがtrueの限りはループ
    //メッセージループに代わる処理にエラーが起きたら終わる
    while (mbRunning&& ProcessMessage() != -1)
    {
        //画面を初期化
        ClearDrawScreen();
        //更新
        Update();
        //描画
        Draw();
        //画面に出す
        ScreenFlip();
    }
}

bool Game::Initialize()
{
    // ウインドウモードで起動
    ChangeWindowMode(true);
    //画面サイズの設定
    SetGraphMode(mnWindowWidth, mnWindowHeight,32);
    //実行ログを表示するか
    SetOutApplicationLogValidFlag(TRUE);
    //ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
    {
        //エラーが起きたら直ちに終了
        return false;    
    }
    //裏画面描画の設定。ちらつきを防止する
    SetDrawScreen(DX_SCREEN_BACK);
    //ループするように設定
    mbRunning = true;
	return true;
}

void Game::Update()
{
    //エスケープキーを押されたとき
    if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
    {
        //ゲームループを終了させる
        mbRunning = false;
    }
}

void Game::Draw()
{
    //文字の表示
    DrawString(0, 0, "わたしの～お墓の～まえで～", GetColor(255, 255, 255));
}
