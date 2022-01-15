#include "01_Spawn/C02_Cube.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AC02_Cube::AC02_Cube()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
}

void AC02_Cube::BeginPlay()
{
	Super::BeginPlay();
	
	UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Mesh/M_BasicShape_Inst.M_BasicShape_Inst'");
	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);

	FVector location = FVector(100, 0, 70);
	SetActorLocation(location);
	FVector scale = FVector(2, 2, 2);
	SetActorScale3D(scale);
	// float x = 0;
	// float y = 0;
	// float z = 0;
	// FRotator rotator = FRotator(y, z, x);
	SetActorRotation(FRotator::ZeroRotator);
	Mesh->SetRelativeLocation(FVector(500, 0, 0));
}

void AC02_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ZRot += DeltaTime * 300;
	if (ZRot >= 360.0f) ZRot = 0.0f;
	
	CubeScale += DeltaTime * Change;

	if (CubeScale <= 0.9f || CubeScale >= 3.0f) Change *= -1;

	SetActorRotation(FRotator(0.0f, ZRot, 0.0f));

	Mesh->SetRelativeRotation(FRotator(ZRot, 0.0f, 0.0f));
	Mesh->SetRelativeScale3D(FVector(CubeScale, CubeScale, CubeScale));

}

void AC02_Cube::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	Material->SetVectorParameterValue("Color", color);
}
