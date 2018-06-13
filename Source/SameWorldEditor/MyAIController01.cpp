// Fill out your copyright notice in the Description page of Project Settings.

//#include "Landborder.h"   #include "Landborder.h"
#include "MyAIController01.h"

AMyAIController01::AMyAIController01(const FObjectInitializer& PCIP) : Super(PCIP)
{

}

/*
void AMyAIController01::MoveTo()
{
//AMyCharacter01* const Enemy = Cast<AMyCharacter01>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
AMyCharacter01* const Enemy = Cast<AMyCharacter01>(GetOwner());


GEngine->AddOnScreenDebugMessage(-1, 11.0, FColor::Red, "Funk:  MoveTo111111");
if (Enemy != NULL) {
FVector location = FVector(800.f, 100.f, 220.f);
//AMyAIController::MoveToLocation(location, 10.0f, true, true, true);
MoveToLocation(location, 10.0f, true, true, true);
GEngine->AddOnScreenDebugMessage(-1, 11.0, FColor::Red, "Funk:  MoveTo2222222");

}
}
*/