// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

//class MyHUD01;

UCLASS()
class SAMEWORLDEDITOR_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn(const FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MouseYaw(float axix);
	void MousePitc(float axix);
	void Activate();

	void msPresR();
	void msReleaseR();
	void msPresL();
	void msReleaseL();
	
	void msWheelAxis(float Value);
	
	void KeyE_Pres();
	void KeyE_Release();

	
	FVector2D mouseDelta;		// moude  delta
	FVector2D mousePos;        //   mouse position

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* myMesh;
	//UPROPERTY(Category = MySpawn, EditAnywhere)
	//TSubclassOf<AMyCharacter01> MyItemBP;
	//UClass* AMyCharacter01_var;
	
	
	
	//APlayerController* pc;

	void PossesTo();
	void KeyCTRL_Release();

	float DTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MY-----CHaracteristick----MY")
		class ASameWorldEditorGameModeBase *gmd;
};
