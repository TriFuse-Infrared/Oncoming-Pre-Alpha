// All rights reserved Trifuse. Written by AidoP

#include "OncomingPreAlpha.h"
#include "JetpackItem.h"


AJetpackItem::AJetpackItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = true; // Ensure that the item doesn't tick as we don't need to for the base!
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/HatItem")); // Get instance of hat texture
    Icon = IconObj.Object; // Set hat texture to icon
    
    Name = "Jetpack"; // Set the name
    Description = "Fly. You should not have this..."; // Set the description
    Weight = 0.0f; // Set the weight
    
    Storage.Init(NULL, 20);
}

bool isFlying = false;
APlayerCharacter* player1;
void AJetpackItem::QuaternaryClothingPress(APlayerCharacter *player) {
    player1 = player;
    isFlying = true;
    
    player->GetCharacterMovement()->AddImpulse(FVector(0, 0, 350.0f));
}

void AJetpackItem::QuaternaryClothingRelease(APlayerCharacter *player) {
    
    isFlying = false;
    
}


void AJetpackItem::Tick(float DeltaSeconds) {
    if (player1) if (isFlying) player1->GetCharacterMovement()->Velocity = FVector(player1->GetCharacterMovement()->Velocity.X, player1->GetCharacterMovement()->Velocity.Y, 200.0f);
}