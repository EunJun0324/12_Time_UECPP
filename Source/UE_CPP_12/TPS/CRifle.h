#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CRifle.generated.h"

UCLASS()
class UE_CPP_12_API ACRifle : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* GrapMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* UngrapMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		class UCurveFloat* Curve;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;

	FTimeline Timeline;
	FOnTimelineFloat OnTimelineFloat;

public:	
	ACRifle();
	
	static ACRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwnerCharacter);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public :
	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aim();
	void End_Aim();

private:
	bool IsAvaliableAim();

private :
	UFUNCTION()
		void Zooming(float Output);

public :
	FORCEINLINE bool GetEquipped() const { return bEquipped; }
	FORCEINLINE bool GetAiming() const { return bAiming; }

};
