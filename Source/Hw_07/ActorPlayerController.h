// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActorPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HW_07_API AActorPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AActorPlayerController();

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
protected:
	virtual void BeginPlay()override;
};
