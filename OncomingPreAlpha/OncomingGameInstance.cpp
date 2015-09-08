// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "OncomingGameInstance.h"

UItemRegistry* ItemRegistry = NewObject<UItemRegistry>();

UOncomingGameInstance::UOncomingGameInstance(const FObjectInitializer& ObjInit) : Super(ObjInit) {
    UWorld* world = GetWorld();
    if (world) {
        ItemRegistry->AddToRegistry(NULL, "NULL");
        
    }
}