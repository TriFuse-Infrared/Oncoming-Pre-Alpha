// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "ItemRegistry.h"
#include "OncomingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ONCOMINGPREALPHA_API UOncomingGameInstance : public UGameInstance
{
    GENERATED_BODY()
    UOncomingGameInstance(const class FObjectInitializer& PCIP);
	
public:
    
    UItemRegistry* ItemRegistry;
	
};