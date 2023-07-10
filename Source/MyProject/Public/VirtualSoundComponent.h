// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AkGameplayStatics.h"
#include <Camera/CameraComponent.h>
#include "VirtualSoundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UVirtualSoundComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVirtualSoundComponent();

	~UVirtualSoundComponent();

	UAkComponent* akComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ForceCalcPosition();

private:
	APawn* player;
	UCameraComponent* camera;

	void CalcPosition();
};
