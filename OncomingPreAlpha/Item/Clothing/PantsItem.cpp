// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "PantsItem.h"


APantsItem::APantsItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = false; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/PantsItem")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Pants"; // Set the name
    Description = "Poorly designed trousers with no width. You should not have this..."; // Set the description
    Weight = 0.0f; // Set the weight
    
    isPants = true;
}