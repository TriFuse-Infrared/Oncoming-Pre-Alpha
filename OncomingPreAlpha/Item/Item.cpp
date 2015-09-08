// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "Item.h"


// Sets default values
AItem::AItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/Item"));
    Icon = IconObj.Object;
    
    Name = "Core Item";
    Description = "From the core of Oncoming. You should not have this...";
    Weight = 0.0f;
}

// Called when the game starts or when spawned
void AItem::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
    // Not called in this instance as bCanEverTick is false!
}

void AItem::InitMesh(FVector offset, UMeshComponent* mesh) {
    Mesh = mesh;
    
    SetState(ItemState::Inventory);
}

void AItem::SetState(ItemState state) {
    
}


FString AItem::GetName() {
    return Name;
}

FString AItem::GetDescription() {
    return Description;
}

float AItem::GetWeight() {
    return Weight;
}



void AItem::Reload(APlayerCharacter* player) {
    
}


void AItem::PrimaryPress(APlayerCharacter* player) {
    
}

void AItem::PrimaryRelease(APlayerCharacter* player) {
    
}

void AItem::SecondaryPress(APlayerCharacter* player) {
    
}

void AItem::SecondaryRelease(APlayerCharacter* player) {
    
}

void AItem::TertiaryPress(APlayerCharacter* player) {
    
}

void AItem::TertiaryRelease(APlayerCharacter* player) {
    
}

//Clothing use events.

void AItem::PrimaryClothingPress(APlayerCharacter* player) {
    
}

void AItem::PrimaryClothingRelease(APlayerCharacter* player) {
    
}

void AItem::SecondaryClothingPress(APlayerCharacter* player) {
    
}

void AItem::SecondaryClothingRelease(APlayerCharacter* player) {
    
}

void AItem::TertiaryClothingPress(APlayerCharacter* player) {
    
}

void AItem::TertiaryClothingRelease(APlayerCharacter* player) {
    
}

void AItem::QuaternaryClothingPress(APlayerCharacter* player) {
    
}

void AItem::QuaternaryClothingRelease(APlayerCharacter* player) {
    
}

void AItem::QuinaryClothingPress(APlayerCharacter* player) {
    
}

void AItem::QuinaryClothingRelease(APlayerCharacter* player) {
    
}
    