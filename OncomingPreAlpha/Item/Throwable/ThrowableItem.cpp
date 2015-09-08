/*
 
 ____________   ______   ____________   _________  ___      ___   ______   ______
 |____   ____| |  ___ \  |____   ____| |  _______| |  |    |  |  /  ____|  |  ___|
      |  |     | |___) |      |  |     |  |        |  |    |  | |  |       |  |
      |  |     |    __/       |  |     |  |______  |  |    |  |  \  \___   |  |___
      |  |     |  _ \         |  |     |  _______| |  |    |  |   \__   \  |  ___|
      |  |     | | \ \        |  |     |  |        |  |    |  |      \   | |  |
      |  |     | |  \ \   ____|  |___  |  |         \  \__/  /   ____/  /  |  |___
      |__|     |_|   \_\ |___________| |__|          \______/    |_____/   |_____|
 
 
 
 -----------------------------------------------------------------------------------
 
 
 
 Oncoming Throwable Item Code - Written by AidoP, Property of Trifuse
 
 Description - Throwable Item that can be thrown as a weapon with tertiary use (Can be toggled). Handles damage, projectile and collision with world
 
 */

#include "OncomingPreAlpha.h"
#include "ThrowableItem.h"


AThrowableItem::AThrowableItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = false; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/ShirtItem")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Throwable"; // Set the name
    Description = "It throws like a rock, looks like a rock & acts like a rock. You should not have this..."; // Set the description
    Weight = 1.0f; // Set the weight (Important in throwable items for curve and gravity calculations)
    Mass = 1.0f; // Set the mass
}

void AThrowableItem::TertiaryPress(APlayerCharacter* player) {
    Throw(player);
}

void AThrowableItem::Throw(APlayerCharacter* player) {
    player->Utils.GetForwards();
    
}