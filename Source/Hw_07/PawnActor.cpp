// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnActor.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 

// Sets default values
APawnActor::APawnActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//USpringArmComponent 타입의 포인터를 가진 SpringArmcomp (스프링 암 컴포넌트 ) 에 
	// 액터(또는 컴포넌트) 안에 기본 컴포넌트를 생성하고 등록하는 함수로 <U(UClass)SprintArmComponent >
	// 즉 스프링암 클레스 컴포넌트를 초기화 하고 이름은 SpringArm 으로 설정한다.
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// 하위 컴포넌트로 만드는 루트 ( 캐릭터 ) 컴포넌트에 붙이는 코드
	SpringArmComp->SetupAttachment(RootComponent);
	// SpringArmcomp 의 거리를 300.0f 로 설정한다.
	SpringArmComp->TargetArmLength = 300.0f;
	//컨트롤 할떄 스프링 암도 같이 움직이게 해달라
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// 스프링 암 끝부분에 카메라를 붙여달라 라는 내용
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void APawnActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

