#include "UE_CPP_12GameModeBase.h"

AUE_CPP_12GameModeBase::AUE_CPP_12GameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> player(L"Blueprint'/Game/Player/BP_Player.BP_Player_C'");
	if (player.Succeeded()) DefaultPawnClass = player.Class;
}