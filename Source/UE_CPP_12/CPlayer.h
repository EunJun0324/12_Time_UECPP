#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_CPP_12_API ACPlayer : public ACharacter
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

public:
	ACPlayer();

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

};
