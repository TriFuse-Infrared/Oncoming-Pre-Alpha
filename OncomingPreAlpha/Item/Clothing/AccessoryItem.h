// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/Item.h"
#include "AccessoryItem.generated.h"

/**
 * 
 */
UCLASS()
class ONCOMINGPREALPHA_API AAccessoryItem : public AItem
{
	GENERATED_UCLASS_BODY()
	
public:
    
    void AccessoryPress(APlayerCharacter* player);
    void AccessoryRelease(APlayerCharacter* player);
    
};
