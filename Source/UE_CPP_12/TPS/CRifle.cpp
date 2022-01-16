#include "TPS/CRifle.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grap(L"AnimMontage'/Game/Character/Montages/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (grap.Succeeded()) GrapMontage = grap.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> ungrap(L"AnimMontage'/Game/Character/Montages/Rifle/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'");
	if (ungrap.Succeeded()) UngrapMontage = ungrap.Object;

	ConstructorHelpers::FObjectFinder<UCurveFloat> curve(L"CurveFloat'/Game/TPS/Curve_Aim.Curve_Aim'");
	if (curve.Succeeded()) Curve = curve.Object;
}

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwnerCharacter)
{
	FActorSpawnParameters params;
	params.Owner = InOwnerCharacter;

	return InWorld->SpawnActor<ACRifle>(params);
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRifle::Equip()
{
	if (bEquipping) return;

	bEquipping = true;

	if (bEquipped)
	{
		Unequip();
		return;
	}

	OwnerCharacter->PlayAnimMontage(GrapMontage, 2);
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ACRifle::End_Equip()
{ bEquipping = false; }

void ACRifle::Unequip()
{ OwnerCharacter->PlayAnimMontage(UngrapMontage, 2); }

void ACRifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::End_Unequip()
{ bEquipping = false; }

void ACRifle::Begin_Aim()
{
	if (!bEquipped) return;
	if (bEquipping) return;
	if (!IsAvaliableAim()) return;

	bAiming = true;

	USpringArmComponent* springArm =
		Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));

	springArm->TargetArmLength = 100;
	springArm->SocketOffset = FVector(0, 30, 10);

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

}

void ACRifle::End_Aim()
{
	if (!bAiming) return;

	bAiming = false;

	USpringArmComponent* springArm =
		Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));

	springArm->TargetArmLength = 200;
	springArm->SocketOffset = FVector(0, 60, 0);

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

bool ACRifle::IsAvaliableAim()
{
	USpringArmComponent* springArm = 
		Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));

	UCameraComponent* camera =
		Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));

	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();

	return springArm && camera && controller;
}

void ACRifle::Zooming(float Output)
{
}

