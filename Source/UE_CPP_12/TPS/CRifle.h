// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;

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

public :
	FORCEINLINE bool GetEquipped() { return bEquipped; }
};
