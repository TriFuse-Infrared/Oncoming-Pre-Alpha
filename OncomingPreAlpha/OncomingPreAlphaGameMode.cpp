// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "OncomingPreAlphaGameMode.h"
#include "Player/IngameHUD.h"
#include "Player/PlayerCharacter.h"



AOncomingPreAlphaGameMode::AOncomingPreAlphaGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    
    DefaultPawnClass = APlayerCharacter::StaticClass();
    HUDClass = AIngameHUD::StaticClass();
    
}