#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class UE_CPP_12_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;

public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float Delta) override;

private :
	class ACharacter* OwnerCharacter;
};
