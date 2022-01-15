#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Property.generated.h"

UCLASS()
class UE_CPP_12_API AC01_Property : public AActor
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere)
		int A = 10;
	UPROPERTY(EditDefaultsOnly)
		int B;
	UPROPERTY(EditInstanceOnly)
		int C;
	UPROPERTY(VisibleAnywhere)
		int D;

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
		int Var = 60;


public:	
	AC01_Property();

protected:
	virtual void BeginPlay() override;

};
