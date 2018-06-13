// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

//#include "Landborder.h"   #include "Landborder.h"

#include "OtherCharacter.h"

#include "AI/Navigation/NavigationPath.h"
#include "MyAIController01.h"
#include "Engine.h"

//////////////////////////////////////////////////////////////////////////
// ALandborder15Character

AOtherCharacter::AOtherCharacter(const FObjectInitializer& PCIP)  : Super(PCIP)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)

}

void AOtherCharacter::BeginPlay()
{
//======================     MOVE_TO_LOCATION     =====================
	AMyAIController01* ai = Cast<AMyAIController01>(GetController());
	if (ai != NULL) {
		FVector location = FVector(-800.f, -200.f, 220.f);
		ai->MoveToLocation(location, 10.0f, true, true, true);
		//GEngine->AddOnScreenDebugMessage(-1, 11.0, FColor::Red, "Funk:  MoveTo");
	}
	//----------------------------------------------------------------------
}

void AOtherCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AOtherCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AOtherCharacter::GoToPoint(FVector& point)
{
	//FHitResult hitResult;
	//PlayerController = Cast<APlayerController>(GetController());
	//PlayerController->GetHitResultUnderCursor(ECC_Pawn, false, hitResult);

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "HIT: ok");

	//UNavigationSystem* NavSys = GetWorld()->GetNavigationSystem();
	UNavigationPath *path;
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
	if (NavSys) {

		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "NavSys: ok" );

		path = NavSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), FVector(0,0,0));

		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "path: ok");

		if (path != NULL)
		{
			for (int pointiter = 0; pointiter < path->PathPoints.Num(); pointiter++)
			{
				DrawDebugSphere(GetWorld(), path->PathPoints[pointiter], 10.0f, 12, FColor(255, 255, 0), false, 5.f);
				NavSys->SimpleMoveToLocation(GetController(), FVector(0,0,0));
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 11.0, FColor::Red, "Funk:  TraceFromSelf");
}
