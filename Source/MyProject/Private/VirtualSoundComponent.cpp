// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualSoundComponent.h"



#include "AkComponent.h"
#include "MyProjectCharacter.h"

// Sets default values for this component's properties
UVirtualSoundComponent::UVirtualSoundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	akComponent = CreateDefaultSubobject<UAkComponent>("VirtualSoundSource");
	bTickInEditor = false;
}

UVirtualSoundComponent::~UVirtualSoundComponent()
{
}


// Called when the game starts
void UVirtualSoundComponent::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld())
	{
		player = GetWorld()->GetFirstPlayerController()->GetPawn();
		//camera = static_cast<AMyProjectCharacter*>(GetWorld()->GetFirstPlayerController()->GetCharacter())->GetFollowCamera();
	}
}


// Called every frame
void UVirtualSoundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CalcPosition();
}

void UVirtualSoundComponent::ForceCalcPosition()
{
	if(GetWorld())
	{
		player = GetWorld()->GetFirstPlayerController()->GetPawn();
		//camera = static_cast<AMyProjectCharacter*>( GetWorld()->GetFirstPlayerController()->GetCharacter())->GetFollowCamera();
	}
	CalcPosition();
}

void UVirtualSoundComponent::CalcPosition()
{
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(GetWorld() && player)
	{
		FVector playerLocation = player->GetActorLocation();

		FVector cameraLocation = FAkAudioDevice::Get()->GetSpatialAudioListener()->GetPosition();

		FVector originLocation = GetOwner()->GetActorLocation();

		float distance = (originLocation - playerLocation).Length();

		FVector direction = originLocation - cameraLocation;
		direction.Normalize();

		akComponent->SetWorldLocation(cameraLocation + (direction * distance));

		DrawDebugLine(GetWorld(),originLocation,akComponent->GetPosition(),FColor::Blue,false,0,1,10);
	}
}

