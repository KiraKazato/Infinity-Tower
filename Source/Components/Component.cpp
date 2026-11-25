#include "Component.h"

Component::Component()
{

}

void Component::SetCharacter(Character* _character)
{
	mCharacter = _character;
}

Character*Component::GetCharacter() const
{
	return mCharacter;
}

void Component::Init()
{
}

void Component::Update()
{
}

void Component::Draw()
{
}