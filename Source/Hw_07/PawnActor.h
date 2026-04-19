// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnActor.generated.h"

class UStaticMesh;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UBoxComponent;
struct FInputActionValue;
UCLASS()
class HW_07_API APawnActor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public :
	UPROPERTY(visibleAnywhere, BluePrintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(visibleAnywhere, BluePrintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(visibleAnywhere, BluePrintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* SK_MeshComp;

	UPROPERTY(visibleAnywhere, BluePrintReadOnly, Category = "Mesh")
	UBoxComponent* BoxComp;

	
protected:

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void MoveUpDown(const FInputActionValue& value);
	UFUNCTION()
	void LookRoll(const FInputActionValue& value);

public:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Speed")
	float fNormalSpeed;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Speed")
	float fAirSpeed;
private:
	bool LineTrace();
	void MoveDownGravity(const float& DeltaTime);
	FTransform MovingSpeed(float X  , float Y , float Z );

	bool bAirCheck;

};
