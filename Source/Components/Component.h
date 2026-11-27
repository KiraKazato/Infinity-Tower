#pragma once



class Component
{
	//Object(本体)がprivateを触れるようにclassの中でfriendをつけて前方宣言
	friend class GameObject;
public:
	Component();
	//派生クラスを正しく破棄するように。
	virtual ~Component() = default;
	//Object(本体)に追加された瞬間に呼ばれる関数
	virtual void Initialize();
	//更新処理
	virtual void Update();
	//描画が必要なComponent(部品)に継承させる描画処理
	virtual void Draw();
	//Component(部品)は書き換えない。Object(本体)は変更可能。
	//GameObject(親)のほかのComponentを見るため
	GameObject* GetGameObject()const;
	//Component(部品)の有効状態の設定
	void SetActive(bool _actived) { mbActived = _actived; }
	//Component(部品)の有効状態の取得
	//Component(部品)を書き換えずフラグを見るためだけのconst
	bool IsActive() const { return mbActived; }

private:
	//Component(部品)を所有するObject(本体)の登録
	void SetGameObject(GameObject* _gameObject);

	//Component(部品)がアタッチされてるObject(本体)のポインタ
	GameObject* mGameObject = nullptr;
	//Component(部品)が動いているか
	bool mbActived = true;
};