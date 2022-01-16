#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPS/IRifle.h"

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
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter);

	if (rifle) 
	{ 
		bEquipped = rifle->Get_Equipped_Rifle();
		bAiming = rifle->Get_Aiming_Rifle();
	}
}
