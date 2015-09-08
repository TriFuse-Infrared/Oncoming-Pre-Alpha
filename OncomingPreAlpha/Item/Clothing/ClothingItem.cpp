// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "ClothingItem.h"
#include "OncomingGameInstance.h"



AClothingItem::AClothingItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/HUD/DefaultIcons/ClothingItem"));
    Icon = IconObj.Object;
    
    Storage.Init(NULL, 10);
    
    Name = "Clothing";
    Description = "Is it a hat, shoes or a vest? Who cares. You should not have this...";
    BaseWeight = 0.0f;
    if(GetWorld()) {
        AddToStorage(GetWorld()->SpawnActor<AItem>());
        AddToStorage(GetWorld()->SpawnActor<AItem>());
        AddToStorage(GetWorld()->SpawnActor<AItem>());
        AddToStorage(GetWorld()->SpawnActor<AItem>());
        AddToStorage(GetWorld()->SpawnActor<AItem>());
        AddToStorage(GetWorld()->SpawnActor<AItem>());
    }
    
    
    UpdateWeight();
}

void AClothingItem::UpdateWeight() {
    float newWeight = BaseWeight;
    
    for (auto& item : Storage) {
        if(item) {
            newWeight += item->Weight;
        }
    }
    
    Weight = newWeight;
}

bool AClothingItem::AddToStorage(AItem *Item) {
    int iteration = 0;
    for (auto& item : Storage) {
        if(!item) {
            Storage.Insert(Item, iteration);
            Storage.RemoveAt(iteration + 1);
            return true;
        }
        iteration++;
    }
    
    return false;
}

int AClothingItem::CalculateStorageUsed() {
    int items = 0;
    
    for (auto& item : Storage) {
        if(item) {
            items++;
        }
    }
    return items;
}