#pragma once
#include "DxLib.h"

class Character;

class Component
{
public:
	Component();
	//派生クラスを正しく破棄するように。
	virtual ~Component() = default;

	//所有するCharacterの登録
	void SetCharacter(Character* _character);
	//Component自身は書き換えない。Characterは変更可能。
	Character*GetCharacter()const;

	//キャラクターに追加された瞬間に呼ばれる関数
	virtual void Init();

	//更新処理
	virtual void Update();

	//描画が必要なコンポーネントに継承させる描画処理
	virtual void Draw();
protected:
	//自分がアタッチされてるキャラクターのポインタ
	Character* mCharacter = nullptr;
};