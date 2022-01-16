#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IRifle.generated.h"

UINTERFACE(MinimalAPI)
class UIRifle : public UInterface
{
	GENERATED_BODY()
};

class UE_CPP_12_API IIRifle
{
	GENERATED_BODY()

public:
	virtual void Begin_Equip_Rifle() = 0;
	virtual void End_Equip_Rifle() = 0;

	virtual void Begin_Unequip_Rifle() = 0;
	virtual void End_Unequip_Rifle() = 0;

	virtual bool Get_Equipped_Rifle() = 0;
};
