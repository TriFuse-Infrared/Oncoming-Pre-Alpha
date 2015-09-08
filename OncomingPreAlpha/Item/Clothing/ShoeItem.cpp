// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "ShoeItem.h"


AShoeItem::AShoeItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = false; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/ShoeItem")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Shoes"; // Set the name
    Description = "In any other game, these would let you run super fast! You should not have this..."; // Set the description
    Weight = 0.0f; // Set the weight
    
    isShoes = true;
}