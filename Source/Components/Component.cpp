#include "Component.h"

Component::Component():mGameObject(nullptr),mbActived(true)
{

}

void Component::SetGameObject(GameObject* _gameObject)
{
	mGameObject = _gameObject;
}

GameObject*Component::GetGameObject() const
{
	return mGameObject;
}

void Component::Initialize()
{
}

void Component::Update()
{
}

void Component::Draw()
{
}