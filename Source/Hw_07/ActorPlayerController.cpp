// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPlayerController.h"
#include "EnhancedInputSubsystems.h"

AActorPlayerController::AActorPlayerController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	UpdownAction(nullptr),
	RollAction(nullptr)
{

}

void AActorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// GetLocalPlayer 는 현제 플레이어에 ( 사용자가 하고 있는 ) 로컬 플레이어 객체를 가져와라 로컬플레이어는 
	// 로컬플레이어는 플레이어의 입력이나 화면 뷰같은 객체를 가져오라고 한것이다.
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		// Enhanced는 IMC를 관리하는 시스템을 따로 있어서 
		// 와씨 어렵다.
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem< UEnhancedInputLocalPlayerSubsystem>())
		{
			// 인풋메핑 컨텍스트가 존제한다면
			if (InputMappingContext)
			{
				// AddMappingContext라는 함수로 활성화 시켜주세요
				SubSystem->AddMappingContext(InputMappingContext, 0);
				// 맨 뒤에는 우선순위 ?... ( 가장 높은 우선순위로 현재 지금 우리가 만든 IMC를 플레이어한태 활성화 시켜라)

			}

		}
	}
}


