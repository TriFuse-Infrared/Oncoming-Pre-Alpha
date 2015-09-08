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
 
 
 
 Oncoming Base Hat Class Code - Written by AidoP, Property of Trifuse
 
 Description - Hat Item Parent, the base for all items equipable in the hat slot
 
 */

#include "OncomingPreAlpha.h"
#include "HatItem.h"


AHatItem::AHatItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = false; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/HatItem")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Hat"; // Set the name
    Description = "A not very not so non-magical hat. You should not have this..."; // Set the description
    Weight = 0.0f; // Set the weight
}