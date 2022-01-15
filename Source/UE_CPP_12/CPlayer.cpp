#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength         = 200;
	SpringArm->bDoCollisionTest        = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset			   = FVector(0, 60, 0);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(L"SkeletalMesh'/Game/Character/Mesh/SK_Code-39-1.SK_Code-39-1'");
	if (mesh.Succeeded()) GetMesh()->SetSkeletalMesh(mesh.Object);
	GetMesh()->SetRelativeLocation(FVector (0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90 ,0));

	TSubclassOf<UAnimInstance> animInstance;
	ConstructorHelpers::FClassFinder<UAnimInstance> anim(L"AnimBlueprint'/Game/Player/BP_CAnimInstance.BP_CAnimInstance_C'");
	if (anim.Succeeded()) animInstance = anim.Class;
	GetMesh()->SetAnimInstanceClass(animInstance);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",    this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",      this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook",   this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom",           this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

}

void ACPlayer::OnMoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACPlayer::OnMoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACPlayer::OnHorizontalLook(float AxisValue)
{ AddControllerYawInput(AxisValue); }

void ACPlayer::OnVerticalLook(float AxisValue)
{ AddControllerPitchInput(AxisValue); }

void ACPlayer::OnZoom(float AxisValue)
{
	SpringArm->TargetArmLength += (ZoomSpeed * AxisValue * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, ZoomRange.X, ZoomRange.Y);
}

void ACPlayer::OnRun()
{ GetCharacterMovement()->MaxWalkSpeed = 600; }

void ACPlayer::OffRun()
{ GetCharacterMovement()->MaxWalkSpeed = 400; }

