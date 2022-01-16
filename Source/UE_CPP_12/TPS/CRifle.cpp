#include "TPS/CRifle.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Weapons/Meshes/SK_AR4.SK_AR4'");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grap(L"AnimMontage'/Game/Character/Montages/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (grap.Succeeded()) GrapMontage = grap.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> ungrap(L"AnimMontage'/Game/Character/Montages/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (ungrap.Succeeded()) GrapMontage = ungrap.Object;
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

