#include "TPS/CAnimNotifyState.h"
#include "TPS/IRifle.h"


FString UCAnimNotifyState::GetNotifyName_Implementation() const
{ return "Equip"; }

void UCAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (!MeshComp) return;

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	if (!rifle) return;

	if (bUnequip)
	{
		rifle->Begin_Unequip_Rifle();
		return;
	}

	rifle->Begin_Equip_Rifle();
}

void UCAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (!MeshComp) return;

	IIRifle* rifle = Cast<IIRifle>(MeshComp->GetOwner());
	if (!rifle) return;

	if (bUnequip)
	{
		rifle->End_Unequip_Rifle();
		return;
	}

	rifle->End_Equip_Rifle();
}
