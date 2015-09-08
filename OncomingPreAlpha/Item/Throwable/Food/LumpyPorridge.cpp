// All rights reserved Trifuse. Written by AidoP

#include "OncomingPreAlpha.h"
#include "LumpyPorridge.h"


ALumpyPorridge::ALumpyPorridge(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = true; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/Items/LumpyPorridgeIcon")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Porridge"; // Set the name
    Description = "Well preserved lumpy porridge. So good it will make you cry."; // Set the description
    Weight = 0.75f; // Set the weight
    Mass = 1.25f; // Set the mass for calculating shit
}