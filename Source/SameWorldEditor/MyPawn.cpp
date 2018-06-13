// Fill out your copyright notice in the Description page of Project Settings.

//#include "Landborder.h"  #include "Landborder.h"
#include "MyPawn.h"

#include "SameWorldEditorGameModeBase.h"
#include "MyCharacter.h"
#include "Engine.h"


// Sets default values
AMyPawn::AMyPawn(const FObjectInitializer& PCIP)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>RockMesh(TEXT("/Game/StarterContent/Props/MaterialSphere.MaterialSphere"));
	myMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("myMesh"));
	RootComponent = myMesh;
	myMesh->SetStaticMesh(RockMesh.Object);

	//myMesh->SetCollisionObjectType(ECC_Pawn);
	myMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//myMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	myMesh->SetCollisionProfileName(TEXT("Pawn"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->TargetArmLength = 700.0f;
	SpringArm->SetWorldRotation(FRotator(-60.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


	

	


	//SetActorTickEnabled(true);

}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	//******   Game MOod       *******************    //  !!!!! PRROVERIT NA VILETANIE
	gmd = Cast<ASameWorldEditorGameModeBase>(UGameplayStatics::GetGameMode(this));
	//******   Game MOod  END  *******************

}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//pc->GetMousePosition(mousePos.X, mousePos.Y);


	//***************************************************************************************
	//*******************            MOUS ROTATION around pawn              ************************
	if ( gmd && gmd->bMousR == true)
	{
		FRotator newYaw = GetActorRotation();
		newYaw.Yaw += mouseDelta.X;
		SetActorRotation(newYaw);

		FRotator newPitch = SpringArm->GetComponentRotation();
		newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseDelta.Y, -80.f, 0.f);
		SpringArm->SetWorldRotation(newPitch);
	}
	//***************************************************************************************

	DTime = DeltaTime;
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//check(PlayerInputComponent);   //77777777777777777777777777777777777
	InputComponent->BindAxis("TurnX", this, &AMyPawn::MouseYaw);
	InputComponent->BindAxis("TurnY", this, &AMyPawn::MousePitc);
	InputComponent->BindAxis("msWheelAxis", this, &AMyPawn::msWheelAxis);
	
	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);

	InputComponent->BindAction("msR", IE_Pressed, this, &AMyPawn::msPresR);		// najatie
	InputComponent->BindAction("msR", IE_Released, this, &AMyPawn::msReleaseR);   //  otjatit
	InputComponent->BindAction("msL", IE_Pressed, this, &AMyPawn::msPresL);
	InputComponent->BindAction("msL", IE_Released, this, &AMyPawn::msReleaseL);
	
	InputComponent->BindAction("KeyE", IE_Pressed, this, &AMyPawn::KeyE_Pres);
	InputComponent->BindAction("KeyE", IE_Released, this, &AMyPawn::KeyE_Release);
	
	InputComponent->BindAction("CTRL", IE_Released, this, &AMyPawn::KeyCTRL_Release);
	

	InputComponent->BindAction("Activate", IE_Pressed, this, &AMyPawn::Activate);

}


//****************************************************************************************
void AMyPawn::MouseYaw(float axix)
{
	mouseDelta.X = axix;
}

void AMyPawn::MousePitc(float axix)
{
	mouseDelta.Y = -axix;
}

void AMyPawn::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		FVector ActorLocation1 = FVector(Value, 0.f, 0.f);
		AddActorLocalOffset(ActorLocation1 * 400.f * DTime, false);
	}
}

void AMyPawn::MoveRight(float Value)
{
	FVector ActorLocation1 = FVector(0.f, Value, 0.f);
	AddActorLocalOffset(ActorLocation1 * 400.f * DTime, false);
}

	
void AMyPawn::msPresR()
{
	if(gmd ){	gmd->bMousR = true;	}
}

void AMyPawn::msPresL()
{
	if(gmd ){	gmd->bMousL = true;	}
}

void AMyPawn::msReleaseR()
{
	if(gmd ){	gmd->bMousR = false;	}
}

void AMyPawn::msReleaseL()
{
	if(gmd ){	gmd->bMousL = false;	}
	//pc = Cast<APlayerController>(GetController());     //+++++++++++++++++++++++++++++++++++
		
	//**********************************************************
	FHitResult hitResult;
	if(gmd->pc)
	{
		gmd->pc->GetHitResultUnderCursor(ECC_Pawn, false, hitResult);
	}
	if (hitResult.bBlockingHit) {
		AActor* const hitActor = hitResult.GetActor();
		if (hitActor) {
			
		/*	AMyCharacterManequen01 *MyManequenTemp = Cast<class AMyCharacterManequen01>(hitActor);
			AMyActorITEM *myItemTemp = Cast<class AMyActorITEM>(hitActor);

			if (myItemTemp)
			{
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "myITEM");
			}
			*/
		/*	if (Actor01)
			{
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "myActor01");
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::FromInt(Actor01->GetUniqueID()));

				FVector Pos1 = Actor01->GetTransform().GetLocation();
				Actor01->SetActorLocation(Pos1 + FVector(300.0f, 0.0f, 0.0f), true);
			}*/
		/*	else if (MyManequenTemp)
			{
				myspawnActor = MyManequenTemp;
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::FromInt(MyManequenTemp->GetUniqueID()));
			}
			else {
				//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "YAY!!!");
				if (myspawnActor) {
					myspawnActor->MyTraceFromSelf(hitResult);
				}
			}
			*/
		}

	}
	
	// Отрисовка нашего луча
	DrawDebugLine(
		GetWorld(),
		Camera->GetComponentLocation(),//GetActorLocation(),
		hitResult.Location,//TraceEnd,
		FColor::Cyan,
		false,	// будет ли наш луч отрисовываться постоянно
		3.0f,	// сколько времени он будет отрисовываться
		0,
		5.0f);	// Толщина луча. Доступна не для всех функций


		
}

void AMyPawn::msWheelAxis(float Value)
{
	if ((Value != 0.0f))
	{
		//FVector ActorLocation1 = FVector(Value, 0.f, 0.f);
		SpringArm->TargetArmLength += SpringArm->TargetArmLength * Value * 0.10f;
	}
}
void AMyPawn::KeyE_Pres()
{
	//****************************     Spawn   **********************
/*

	// PC = Cast<APlayerController>(GetController());   // in Constructor
	FHitResult hitResult;
	//Controller->CastToPlayerController()->GetHitResultUnderCursor(ECC_Pawn, false, hitResult);
	PC->GetHitResultUnderCursor(ECC_Pawn, false, hitResult);
	UWorld* const World = GetWorld();
	//FActorSpawnParameters SpawnParams;            // maybe need for SpawnActor, if need param
	//SpawnParams.Owner = this;
	//SpawnParams.Instigator = Instigator;
	if (World != NULL) {
		if (mySpawnItem) {
			mySpawnItem = World->SpawnActor<AMyActorITEM>(mySpawnItem, hitResult.ImpactPoint, FRotator::ZeroRotator);
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::FromInt(myspawnActor->GetUniqueID()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "NoN--NoN");
		}
	}
*/	//****************************     Spawn  END   **********************

	
}

void AMyPawn::KeyE_Release()
{

}

void AMyPawn::KeyCTRL_Release()
{
	gmd->PlayerPosses();
}

void AMyPawn::PossesTo()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void AMyPawn::Activate()
{
	FString SaveDirectory = FString("/ttt.txt");
	FString SaveText = FString("#>(1)-aaa-(2)-bbbb-(3)-ccccc-#}|#>(1)-aaa11-(2)-bbbb11-(3)-ccccc11-#}|#>(1)-aaa222-(2)-bbbb222-(3)-ccdccc222-#}|");

	FFileHelper::SaveStringToFile(SaveText, *SaveDirectory);

	// (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*AbsoluteFilePath))
	// if( ! FPlatformFileManager::Get().GetPlatformFile().MoveFile(AbsoluteDestinationPath, AbsoluteSourcePath))
	// const int64 FileSize = FPlatformFileManager::Get().GetPlatformFile().FileSize(*SaveDirectory);
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*SaveDirectory))
	{
		FString fileContent = FString("");
		FFileHelper::LoadFileToString(fileContent, *SaveDirectory);

		int32 n1 = fileContent.Find(FString("#>"), ESearchCase::CaseSensitive, ESearchDir::FromStart, 0);    //  ESearchCase::IgnoreCase,  ESearchDir::FromStart
		int32 n2 = fileContent.Find(FString("(1)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		int32 n3 = fileContent.Find(FString("(2)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		int32 n4 = fileContent.Find(FString("(3)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		int32 n5 = fileContent.Find(FString("#}"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, FString::FromInt(n1));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, FString::FromInt(n2));
		FString SaveText2 = fileContent.Mid(n2 + 3, n3 - n2 - 3);
		FString SaveText3 = fileContent.Mid(n3 + 3, n4 - n3 - 3);
		FString SaveText4 = fileContent.Mid(n4 + 3, n4 - n3 - 2);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText2);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText3);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText4);

		n1 = fileContent.Find(FString("#>"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n5);    //  ESearchCase::IgnoreCase,  ESearchDir::FromStart
		n2 = fileContent.Find(FString("(1)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		n3 = fileContent.Find(FString("(2)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		n4 = fileContent.Find(FString("(3)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		n5 = fileContent.Find(FString("#}"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, FString::FromInt(n1));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, FString::FromInt(n2));
		SaveText2 = fileContent.Mid(n2 + 3, n3 - n2 - 3);
		SaveText3 = fileContent.Mid(n3 + 3, n4 - n3 - 3);
		SaveText4 = fileContent.Mid(n4 + 3, n4 - n3 - 2);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText2);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText3);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText4);

		n1 = fileContent.Find(FString("#>"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n5);    //  ESearchCase::IgnoreCase,  ESearchDir::FromStart
		n2 = fileContent.Find(FString("(1)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		n3 = fileContent.Find(FString("(2)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		n4 = fileContent.Find(FString("(3)"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		n5 = fileContent.Find(FString("#}"), ESearchCase::CaseSensitive, ESearchDir::FromStart, n1);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, FString::FromInt(n1));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, FString::FromInt(n2));
		SaveText2 = fileContent.Mid(n2 + 3, n3 - n2 - 3);
		SaveText3 = fileContent.Mid(n3 + 3, n4 - n3 - 3);
		SaveText4 = fileContent.Mid(n4 + 3, n4 - n3 - 2);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText2);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText3);
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Yellow, SaveText4);
	}
}