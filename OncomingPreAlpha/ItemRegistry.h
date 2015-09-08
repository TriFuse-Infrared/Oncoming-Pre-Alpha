// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "ItemRegistry.generated.h"

/**
 * 
 */
UCLASS()
class ONCOMINGPREALPHA_API UItemRegistry : public UObject
{
	GENERATED_BODY()
	
public:
    
    bool AddToRegistry(class AItem* Item, FString ID);
    class AItem* GetID(FString ID);
    
    TMap<FString, class AItem*> Registry;
	
	
};