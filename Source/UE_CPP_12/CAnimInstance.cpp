#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float Delta)
{
	Super::NativeUpdateAnimation(Delta);

	if (!OwnerCharacter) return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
}
