// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "AkComponent.h"
#include "MyProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "MyProjectCharacter.h"
#include "AkGameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

void AMyPlayerController::AddPawnToList(APawn* pawn)
{
	if(pawn != nullptr)
		Pawns.EmplaceAt(0,pawn);
}

void AMyPlayerController::SwapPawn()
{
	// don't allow swapping during a swap
	if(!CompletedSwap)
		return;

	// get the rotation of the current pawn before possessing
	MyPrevProjectCharacter = static_cast<AMyProjectCharacter*>(Pawns[PawnIndex]);
	FRotator oldRotate = GetControlRotation();
	PawnIndex = (PawnIndex + 1) % Pawns.Num();
	// ProbePosition is only updated during swapping so start it at the pawn's position
	ProbePosition = MyPrevProjectCharacter->GetActorLocation();

	// not used???
	AMyProjectCharacter* MyProjectCharacter = static_cast<AMyProjectCharacter*>(Pawns[PawnIndex]);

	// switch the state to swapping
	CompletedSwap = false;
	SwappingTime = 0.0f;

	// remove the camera from the pawn's camera boom
	ViewActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	// take control of the next pawn
	Possess(Pawns[PawnIndex]);

	// set the camera boom of the new pawn to the same as the old pawn
	SetControlRotation(oldRotate);
}

AMyPlayerController::AMyPlayerController()
{
	// critical to turn of auto manage 
	bAutoManageActiveCameraTarget = false;
	bAttachToPawn = true;

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// instantiate an actor for the camera to attach to
	ViewActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetPawn()->GetActorLocation(),GetPawn()->GetActorRotation());

	// attach a camera to the actor
	FollowCamera = static_cast<UCameraComponent*> (ViewActor->AddComponentByClass(UCameraComponent::StaticClass(),false,FTransform(),false));
	FollowCamera->bUsePawnControlRotation = false;

	// attach the actor to the starting active character's camera boom
	AMyProjectCharacter* MyProjectCharacter = static_cast<AMyProjectCharacter*>(GetPawn());
	ViewActor->AttachToComponent(MyProjectCharacter->GetCameraBoom(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),USpringArmComponent::SocketName);

	// Set the view to the created camera
	SetViewTarget(ViewActor);

	// wwise code to attach the Default Listener to the camera actor
	UAkComponent* CameraListener = FAkAudioDevice::Get()->GetAkComponent(PlayerCameraManager->GetRootComponent(),FName(),NULL,EAttachLocation::SnapToTarget);
	CameraListener->AttachToComponent(ViewActor->GetRootComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);

}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// if swapping
	if(!CompletedSwap)
	{
		SwappingTime += DeltaSeconds;
		AMyProjectCharacter* MyProjectCharacter = static_cast<AMyProjectCharacter*>(Pawns[PawnIndex]);

		// Lerp the camera to the new boom location
		FVector Location = FMath::Lerp(ViewActor->GetActorLocation(),MyProjectCharacter->GetCameraBoom()->GetSocketLocation(USpringArmComponent::SocketName),SwappingTime/TimeToSwap);
		ViewActor->SetActorLocation(Location);

		// in theory doesn't do anything bc the new and old rotation should be identical, but slerps in case of changed rotation
		FQuat Rotation = FQuat::Slerp(ViewActor->GetActorQuat(),FQuat(MyProjectCharacter->GetControlRotation()),SwappingTime/TimeToSwap);
		ViewActor->SetActorRotation(Rotation);

		// lerp the probe to the new pawn location
		ProbePosition = FMath::Lerp(ProbePosition,MyProjectCharacter->GetActorLocation(),SwappingTime/TimeToSwap);

		// after completing swap
		if(SwappingTime >= TimeToSwap)
		{
			// attach the camera to the new pawns camera boom
			CompletedSwap = true;
			ViewActor->AttachToComponent(MyProjectCharacter->GetCameraBoom(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),USpringArmComponent::SocketName);
		}
		
	}

	DrawDebugCircle(GetWorld(),GetProbePosition(),100.0f,10,FColor::Red);
}

FVector AMyPlayerController::GetProbePosition()
{
	// if swapping return the probe position that is being updated by swap
	if(!CompletedSwap)
	{
		return ProbePosition;
	}
	// if the swap is complete probe should be at the current pawn
	else
	{
		return Pawns[PawnIndex]->GetActorLocation();
	}
}


