// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Add's a pawn to the owned pawns list
	void AddPawnToList(class APawn* pawn);

	// switches the active pawn
	void SwapPawn();

	AMyPlayerController();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	// Function to get the location of the listener probe
	UFUNCTION(BlueprintCallable, Category =Listener)
	FVector GetProbePosition();

private:
	// Array of pawns that are controlled by this controller
	UPROPERTY()
	TArray<class APawn*> Pawns;

	// current possessed pawn
	int PawnIndex = 0;

	/** Follow camera that is passed across sisters */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Actor that the camera is attached to
	AActor* ViewActor;

	// Timer tracking swapping
	float SwappingTime = 0.0f;

	// Length of swap, possibly defunct
	static constexpr float TimeToSwap = 1.5f;

	// bool tracking if swapping
	bool CompletedSwap = true;

	// Vector tracking listener probe position during a swap
	FVector ProbePosition;

	// pointer to the previously possessed pawn
	class AMyProjectCharacter* MyPrevProjectCharacter;
};
