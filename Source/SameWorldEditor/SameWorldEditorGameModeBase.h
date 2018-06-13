// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SameWorldEditorGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMEWORLDEDITOR_API ASameWorldEditorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
ASameWorldEditorGameModeBase(const FObjectInitializer& PCIP);
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	FTimerHandle delay;
	void Delay();

public:	

	UPROPERTY(Category = MySpawn, EditAnywhere)
		TSubclassOf<class AMyCharacter> MyPlayerBP;     //  Dont forget
	UPROPERTY(Category = MySpawn, EditAnywhere)
		TSubclassOf<class AMyPawn> MyCameraBP;     //  Dont forget
		
	void PlayerPosses();
	void CameraPosses();
	
	class AMyPawn *Camera;
	class AMyCharacter *Player;
	
	APlayerController* pc;
	
	FVector2D mousePos;
	
	bool bMousR;
	bool bMousL;	
	
};
