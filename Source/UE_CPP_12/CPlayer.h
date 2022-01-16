#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS/IRifle.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_CPP_12_API ACPlayer : 
	public ACharacter,
	public IIRifle
{
	GENERATED_BODY()

private :
	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float ZoomSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		FVector2D ZoomRange = FVector2D(0, 500);

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private :
	class ACRifle* Rifle;

public:
	ACPlayer();

public :
	virtual void Begin_Equip_Rifle() override;
	virtual void End_Equip_Rifle() override;

	virtual void Begin_Unequip_Rifle() override;
	virtual void End_Unequip_Rifle() override;

	virtual bool Get_Equipped_Rifle() override;
	virtual bool Get_Aiming_Rifle() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	void OnMoveForward   (float AxisValue);
	void OnMoveRight     (float AxisValue);
	void OnHorizontalLook(float AxisValue);
	void OnVerticalLook  (float AxisValue);
	void OnZoom          (float AxisValue);

	void OnRun();
	void OffRun();

	void OnRifle_Equip();

	void OnAim();
	void OffAim();

};
