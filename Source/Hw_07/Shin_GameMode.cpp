// Fill out your copyright notice in the Description page of Project Settings.


#include "Shin_GameMode.h"
#include "PawnActor.h"
#include "ActorPlayerController.h"

AShin_GameMode::AShin_GameMode()
{
	DefaultPawnClass = APawnActor::StaticClass();
	PlayerControllerClass = AActorPlayerController::StaticClass();
	// 클래스를 할당
}
