// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualSoundAnimNotify.h"

#include "AkComponent.h"
#include "VirtualSoundComponent.h"




void UVirtualSoundAnimNotify::Notify 
	(
		USkeletalMeshComponent * MeshComp,
		UAnimSequenceBase * Animation
	)
{
	// if(MeshComp)
	// {
	// 	if(mSound != nullptr)
	// 	{
	// 		if(helpme->GetWorld()==GetWorld())
	// 			helpme->Destroy();
	// 		mSound = nullptr;
	// 	}
	// 	
	// 	helpme = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), MeshComp->GetComponentLocation(),MeshComp->GetComponentRotation());
	// 	mSound = static_cast<UVirtualSoundComponent*>(helpme->AddComponentByClass(UVirtualSoundComponent::StaticClass(),false,FTransform(),false));
	// 	mSound->akComponent->OcclusionRefreshInterval = 0;
	//
	//
	// 	if(helpme)
	// 	{
	// 		FHitResult f;
	// 		helpme->K2_SetActorLocation(MeshComp->GetComponentLocation(),false,f,false);
	//
	// 		//mSound->ForceCalcPosition();
	//
	// 		if(mSound && mEvent && mSound->akComponent)
	// 			eventID = FAkAudioDevice::Get()->PostAkAudioEventOnComponent(mEvent,mSound->akComponent);
	// 	}
	// }
}

UVirtualSoundAnimNotify::UVirtualSoundAnimNotify() : UAnimNotify()
{
	bShouldFireInEditor = false;
	mSound = nullptr;
	helpme = nullptr;
}

void UVirtualSoundAnimNotify::OnEventEnd(AkCallbackType type, AkCallbackInfo* info)
{
	//FAkAudioDevice::Get()->UnregisterComponent(info->gameObjID);
}


