// Fill out your copyright notice in the Description page of Project Settings.

#include "SameWorldEditorGameModeBase.h"

#include "MyCharacter.h"
#include "MyPawn.h"
#include "Engine.h"





ASameWorldEditorGameModeBase::ASameWorldEditorGameModeBase(const FObjectInitializer& PCIP) : Super(PCIP)
{

	PrimaryActorTick.bCanEverTick = true;
	
	bMousR = false;
	bMousL = false;
}

void ASameWorldEditorGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.Owner = this;
	//SpawnParams.Instigator = Instigator;
	UWorld* const World = GetWorld();
	
	if (MyPlayerBP) {
		Player = World->SpawnActor<AMyCharacter>(MyPlayerBP, FVector(0.f, 200.f, 200.f), FRotator::ZeroRotator);
	}else{
	}
	if (MyCameraBP) {
		Camera = World->SpawnActor<AMyPawn>(MyCameraBP, FVector(0.f,0.f,200.f), FRotator::ZeroRotator);	
	}
	
	GetWorldTimerManager().SetTimer(delay, this, &ASameWorldEditorGameModeBase::Delay, 1.0f, true, 0.5f);
	
	
	//AMyPawn *Camera = GetWorld()->SpawnActor<AMyPawn>(FVector(0.f, 150.f, 200.f), FRotator::ZeroRotator);
	//AMyCharacter *Player = GetWorld()->SpawnActor<AMyCharacter>(FVector(0.f, 0.f, 200.f), FRotator::ZeroRotator);  //++++

	
	
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	pc->bShowMouseCursor = true;
	
	/*
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter01::StaticClass(), foundActorsArray);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActorTerrein::StaticClass(), FoundActors);
	AMyActorTerrein *findActor = Cast<AMyActorTerrein>(FoundActors[0]);
	if (findActor)
	{
		TerreinActor->Click();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, "_____NOT    TERREIN ACTOR_________");
	}
	*/
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, "1");
}

void ASameWorldEditorGameModeBase::Delay()
{
    if (Player)
    {
		PlayerPosses();
        GetWorldTimerManager().ClearTimer(delay);
    }
}

void ASameWorldEditorGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//***************************************************************************************
	//*******************            MOUS POS                 ************************
	//***************************************************************************************
	if (pc)	{
		pc->GetMousePosition(mousePos.X, mousePos.Y);
	}else{
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, "_____NOT    MOUS   POS_________");
	}
	
}

void ASameWorldEditorGameModeBase::PlayerPosses()
{
	pc->Possess(Player);
	//Player->AutoPossessPlayer = EAutoReceiveInput::Player0;;
}
void ASameWorldEditorGameModeBase::CameraPosses()
{
	pc->Possess(Camera);
	//Camera->AutoPossessPlayer = EAutoReceiveInput::Player0;;
}