// All rights reserved Trifuse. Written by AidoP

#include "OncomingPreAlpha.h"
#include "Pepsi.h"


APepsi::APepsi(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = true; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/Items/PepsiIcon")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Pepsi"; // Set the name
    Description = "Because why not? Oh yeh, we will get sued..."; // Set the description
    Weight = 0.56f; // Set the weight
    Mass = 0.9f; // Set the mass for calculating shit
}