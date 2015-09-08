// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "ShirtItem.h"


AShirtItem::AShirtItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = false; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/ShirtItem")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Shirt"; // Set the name
    Description = "Wow! You managed to hack in a useless shirt. You should not have this..."; // Set the description
    Weight = 0.0f; // Set the weight
    
    isShirt = true;
}