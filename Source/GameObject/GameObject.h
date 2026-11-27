#pragma once
#include <string>
#include <memory>
#include <vector>
//ファイル指定
//「/」はパソコンのファイルの中から
//「./」は今のフォルダの中から
//「../」は一個前のフォルダの中から
#include "../Components/Component.h"

class GameObject
{
public:
	//&でアドレス参照、constで書き換え対策
	GameObject(const std::string& _name = "GameObject");
	//派生クラスを正しく破棄するように。
	virtual ~GameObject() = default;
	//unique_ptrを所持しているため、コピーと代入を明示的に禁止
	//住所で渡さなければいけないため&を引数に
	//コピーされる側をいじれないようにconst
	//生成されたObject(本体)をそのままコピーして作るのを禁止
	GameObject(const GameObject&) = delete;
	//生成したObject(本体)を既存のObject(本体)に上書きコピーを禁止
	GameObject& operator = (const GameObject&) = delete;

	//Object(本体)に新しいComponent(部品)を装着
	//...は、可変長引数(可変引数テンプレート)
	// 受け取るときは前に、渡すときは後ろにつける。
	//Argsは英語のArguments(プログラム用語で引数)の略称
	template<class T, class...Args>
	//Component(部品)のポインタを返す
	//&&は、渡された値をそのまま受け取れる
	T* AddComponent(Args&&...args)
	{
		//すでにComponent(部品)が追加されているか
		if (HasComponent<T>())
		{
			//すでにあれば既存のComponent(部品)を返す
			return GetComponent<T>();
		}
		//static_assertはビルド中にエラーを検知
		//is_base_ofは後の型と親子関係かをしらべる。
		//_vは::valueの略
		//最後の文は、表示させるエラーメッセージ
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");
		//make_uniqueは、スマートポインタのunique_ptrを安全に生成する
		//forwardは、無駄なコピーをせず、値をそのまま受け渡す
		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		//Component(部品)を持つオブジェクト(親)を教える
		component->SetGameObject(this);
		//ポインタ(住所)を受け取る
		//実体がある住所を渡せば、サイズを少なく実体を見れるため。
		//所有権が移る前に渡す。
		//mComponentからだと、Tと返す値が合わなくなってしまうため。
		T* componentPtr = component.get();
		//auto componentが持っているComponent(部品)の所有権をmComponentに譲渡
		//unique_ptrは実体のコピーができないため。
		mComponents.push_back(std::move(component));
		//呼び出し側が使えるようにポインタを返す
		return componentPtr;
	}

	template<class T>
	//Object(本体)を書き換えないようにconst
	T* GetComponent() const
	{
		//Object(本体)が持っているComponent(部品)を1つずつチェック
		for (const auto& component : mComponents)
		{
			//GetしたいComponent(部品)を探す
			if (T* target = dynamic_cast<T*>(component.get()))
			{
				//見つけたらポインタ(住所)を返す
				return target;
			}
		}
		//見つからなかったらnullptrを返す
		return nullptr;
	}

	template<class T>
	//Component(部品)を持っているかチェック
	bool HasComponent()const
	{
		//そのComponent(部品)があればtrueを返す
		return GetComponent<T>() != nullptr;
	}

	//すべてのComponent(部品)が追加された後に呼ぶ関数
	//Component(部品)一括初期化するため
	virtual void Initialize();
	//有効な部品の更新処理
	virtual void Update();
	//有効な部品の描画処理
	virtual void Draw();

	//Object(本体)の有効状態の設定
	void SetActive(bool _actived) { mbActived = _actived; }
	//Object(本体)の有効状態の取得
	//Object(本体)を書き換えずフラグを見るためだけのconst
	bool IsActive() const{ return mbActived; }

	//Object(本体)の名前設定
	//&をつけないと文字列のコピーが発生して重くなってしまうため、直接のぞき見させる
	//constでないと文字列を直接受け取ることができないため、引数にconst
	void SetName(const std::string& _name) { mName = _name; }

	//Object(本体)の名前取得
	//&がついてるのはSetと同じ理由
	//Object(本体)と名前を変えないようにconst
	const std::string& GetName()const { return mName; }
private:
	//Object(本体)が動いているか
	bool mbActived = true;
	//Object(本体)の名前
	std::string mName;
	//Object(本体)が消えると、Component(部品)も自動でメモリ解放されるようにunique_ptr
	std::vector<std::unique_ptr<Component>>mComponents;
};