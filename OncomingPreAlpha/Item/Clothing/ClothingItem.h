// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/Item.h"
#include "ClothingItem.generated.h"

/**
 * 
 */
UCLASS()
class ONCOMINGPREALPHA_API AClothingItem : public AItem
{
	GENERATED_UCLASS_BODY()
	
public:
    
    void UpdateWeight();
    int CalculateStorageUsed();
    
    bool AddToStorage(AItem* Item); //Returns false if item could not be added.
    AItem* RemoveFromStorage(int Index); //Returns item removed. NULLItem returned if index is invalid or empty!.
    
    float BaseWeight; // Do not use Weight with AClothingItems as it is dynamic!
    TArray<AItem*> Storage;
	
	
};
