#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState.generated.h"

UCLASS()
class UE_CPP_12_API UCAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		bool bUnequip;

private :
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


};
