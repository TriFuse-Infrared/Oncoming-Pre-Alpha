// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "ItemRegistry.h"


bool UItemRegistry::AddToRegistry(class AItem* Item, FString ID) {
    if(Registry.Contains(ID)) {
        return false;
    }
    
    Registry.Add(ID, Item);
    
    return true;
}

class AItem* UItemRegistry::GetID(FString ID) {
    if (Registry.Contains(ID)) return Registry[ID];
    else return NULL;
}