// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnActor.h"
#include "ActorPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Components/BoxComponent.h"

// Sets default values
APawnActor::APawnActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);

	SK_MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SK_MeshComp->SetupAttachment(BoxComp);
	

	//USpringArmComponent 타입의 포인터를 가진 SpringArmcomp (스프링 암 컴포넌트 ) 에 
	// 액터(또는 컴포넌트) 안에 기본 컴포넌트를 생성하고 등록하는 함수로 <U(UClass)SprintArmComponent >
	// 즉 스프링암 클레스 컴포넌트를 초기화 하고 이름은 SpringArm 으로 설정한다.
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// 하위 컴포넌트로 만드는 루트 ( 캐릭터 ) 컴포넌트에 붙이는 코드
	SpringArmComp->SetupAttachment(BoxComp);
	// SpringArmcomp 의 거리를 300.0f 로 설정한다.
	SpringArmComp->TargetArmLength = 300.0f;
	//컨트롤 할떄 스프링 암도 같이 움직이게 해달라
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// 스프링 암 끝부분에 카메라를 붙여달라 라는 내용
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 100.0f;
	AirSpeed = 70.0f;
}

// Called when the game starts or when spawned
void APawnActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector3d Test = APawnActor::GetActorLocation();
	Test.Z += 50.0f;
	SetActorLocation(Test);

}

void APawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Velocity(0,0,0);

	// 1. 중력 가속도 적용 (Z축)
	Velocity.Z += -980.f * DeltaTime;

	// 2. 위치 이동
	AddActorWorldOffset(Velocity * DeltaTime, true);
}



// Called to bind functionality to input
void APawnActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AActorPlayerController* PlayerController = Cast<AActorPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APawnActor::Move);
				UE_LOG(LogTemp, Warning, TEXT("Forward"));
			}
			if (PlayerController->UpdownAction)
			{
				EnhancedInput->BindAction(
					PlayerController->UpdownAction,
					ETriggerEvent::Triggered,
					this,
					&APawnActor::MoveUpDown);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APawnActor::Look);
			}
			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Triggered,
					this,
					&APawnActor::LookRoll);
			}

		}
	}
}


void APawnActor::Move(const FInputActionValue& value)
{
	if (!Controller)return; // 안정 코드 입력값이 있는지 없는지 확인

	const FVector2D MoveInput = value.Get<FVector2d>(); // 입력값을 2d vector형태 로 저장한다.

	if (!FMath::IsNearlyZero(MoveInput.X)) //  0에 
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds(); //Tick에 있는 DeltaTime을 끌어옴 

		FTransform Test_01; //  값을 초기화 안하면 000 이다.
		Test_01.SetLocation(FVector3d(MoveInput.X, 0, 0));  
		AddActorLocalTransform(Test_01);

		//FVector3d Test = APawnActor::GetActorLocation(); // 궃이 위치좌표를 안가져와두된다.
		//APawnActor::SetActorLocation(Test); // ㅇ... 됬다. 사용시 문제 되는 점 
		// 필요한건 어떤 방식으로 회전해도 local forward로 이동해야하지만 wrold forward로 이동한다는 점이 문제였다.
		// 그래서 필요한건 무엇? Add Actor Local Transform 
		// FTransfrom 은 선언만하고 초기화를 하지않으면 0 0 0 값으로 초기화가 되기 때문에.
		// x좌표값만 추가하면 충분히 사용 가능하다. 
		// 수정후 주석
		
		//AddActorLocalTransform 이걸 사용해야 할 거같은데.
		//UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *GetName());
		//APawnActor::AddActorLocalTransform(Test_01);
		
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds(); //Tick에 있는 DeltaTime을 끌어옴 
		FTransform Test_01; //  값을 초기화 안하면 000 이다.
		Test_01.SetLocation(FVector3d(0,MoveInput.Y,0));
		AddActorLocalTransform(Test_01);

		// 속도 조절 로직 도 따로 작성해보자.
		// WorldLocation 좌표를 수정하는 로직임.
		/*
		FVector3d Test = APawnActor::GetActorLocation();
		Test.Y += MoveInput.Y;
		APawnActor::SetActorLocation(Test); // ㅇ... 됬다.
		*/
		// DeltaTime을 사용해야 하는데 추가할 값이 속도 값이 또 추가 되어야 한다.

	}

}
void APawnActor::MoveUpDown(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2d>(); // 입력값을 2d vector형태 로 저장한다.

	if (!FMath::IsNearlyZero(MoveInput.X))
	{

		float DeltaTime = GetWorld()->GetDeltaSeconds(); //Tick에 있는 DeltaTime을 끌어옴 
		// DeltaTime을 사용해야 하는데 추가할 값이 속도 값이 또 추가 되어야 한다.

		FTransform Test_01; //  값을 초기화 안하면 000 이다.
		Test_01.SetLocation(FVector3d(0, 0, MoveInput.X));
		AddActorLocalTransform(Test_01);
	}
}

void APawnActor::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>() * 100.0f;
	float DeltaTime = GetWorld()->GetDeltaSeconds(); //Tick에 있는 DeltaTime을 끌어옴 

	FRotator Test(0,0,0);
	Test.Yaw += (LookInput.X *DeltaTime );
	Test.Pitch += (-LookInput.Y * DeltaTime);
	AddActorLocalRotation(Test);
	// 속도
	//AddControllerYawInput(LookInput.X); // Yaw 갑은 좌우 회전 x값 
	//AddControllerPitchInput(LookInput.Y); // Pitch 값은 Y값 그리고 Y값은 반전해서 입력해 놓았음
}
void APawnActor::LookRoll(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>() * 100.0f;
	float DeltaTime = GetWorld()->GetDeltaSeconds(); //Tick에 있는 DeltaTime을 끌어옴 

	FRotator Test(0, 0, 0);
	Test.Roll+= (LookInput.X * DeltaTime);
	AddActorLocalRotation(Test);
	UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *LookInput.ToString());

}


