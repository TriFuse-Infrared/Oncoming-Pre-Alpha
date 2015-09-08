// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "AccessoryItem.h"

AAccessoryItem::AAccessoryItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = false;
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/AccessoryItem"));
    Icon = IconObj.Object;
    
    Name = "Accessory";
    Description = "Useless Accessory. You should not have this...";
    Weight = 0.0f;
}

void AAccessoryItem::AccessoryPress(APlayerCharacter *player) {
    
}

void AAccessoryItem::AccessoryRelease(APlayerCharacter *player) {
    
}