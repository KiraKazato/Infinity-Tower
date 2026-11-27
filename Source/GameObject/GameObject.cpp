#include "GameObject.h"

GameObject::GameObject(const std::string& _name) :mName(_name),mbActived(true)
{

}

void GameObject::Initialize()
{
	//所持しているComponent(部品)の初期化を順番に実行kekk
	for (auto& component : mComponents)
	{
		component->Initialize();
	}
}


void GameObject::Update()
{
	//Object(本体)が有効ではないなら更新しない
	if (!mbActived)return;
	//所持しているComponent(部品)のUpdateを順番に実行
	for (auto& component : mComponents)
	{
		//部品が有効の時に通す
		if (component->IsActive())
		{
			component->Update();
		}
	}
}

void GameObject::Draw()
{
	//Object(本体)が有効ではないなら描画しない
	if (!mbActived)return;
	//所持しているComponent(部品)のDrawを順番に実行
	for (auto& component : mComponents)
	{
		//部品が有効の時に通す
		if (component->IsActive())
		{
			component->Draw();
		}
	}
}