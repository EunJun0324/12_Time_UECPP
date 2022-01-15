#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Cube.generated.h"

UCLASS()
class UE_CPP_12_API AC02_Cube : public AActor
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

public:	
	AC02_Cube();

protected:
	virtual void BeginPlay() override;

public :
	virtual void Tick(float DeltaTime) override;

private :
	UFUNCTION()
		void ChangeColor();

private :
	class UMaterialInstanceDynamic* Material;

	float ZRot = 0.0f;
	float CubeScale = 1.0f;
	float Change = 1;
};
