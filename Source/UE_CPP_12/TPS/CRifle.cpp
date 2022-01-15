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

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"");
	if (mesh.Succeeded()) Mesh->SetSkeletalMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grap(L"AnimMontage'/Game/Character/Montages/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (grap.Succeeded()) GrapMontage = grap.Object;

	ConstructorHelpers::FObjectFinder<UAnimMontage> ungrap(L"AnimMontage'/Game/Character/Montages/Rifle/Rifle_Grab_Montage.Rifle_Grab_Montage'");
	if (ungrap.Succeeded()) GrapMontage = ungrap.Object;
}

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwnerCharacter)
{
	return nullptr;
}

void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRifle::Equip()
{
}

void ACRifle::Begin_Equip()
{
}

void ACRifle::End_Equip()
{
}

