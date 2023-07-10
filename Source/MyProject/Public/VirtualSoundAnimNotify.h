// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AkGameplayStatics.h"
#include "VirtualSoundAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UVirtualSoundAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify 
	(
		USkeletalMeshComponent * MeshComp,
		UAnimSequenceBase * Animation
	) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attributes)
	class UAkAudioEvent* mEvent;
	
	class UVirtualSoundComponent* mSound = nullptr;
	int32 eventID;

	AActor* helpme = nullptr;

	UVirtualSoundAnimNotify();
	
private:
	static void OnEventEnd(AkCallbackType type, AkCallbackInfo* info);

};
