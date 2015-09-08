// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerCharacter.h"
#include "IngameHUD.generated.h"

 
UCLASS()
class ONCOMINGPREALPHA_API AIngameHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
	
    
public:    
    void DrawInventory();
    void DrawClothingInventory();
    void DrawSelectedItem();
    
    void DrawQuickSlots();
    
    virtual void DrawHUD() override;
    
    int ConvertClothingSlot(int slot);
    FString ConvertClothingIndexToName(int slot);
    
    UPROPERTY()
    UTexture2D* ItemContainerTex;
    UPROPERTY()
    UTexture2D* SelectedItemContainerTex;
    UPROPERTY()
    UFont* Audiowide;
    UPROPERTY()
    UFont* AudiowideSmall;
    
    UPROPERTY()
    FCanvasIcon ItemContainer;
    UPROPERTY()
    FCanvasIcon SelectedItemContainer;
    
    
    
    float InventorySlideTimespan = 400; //Time to slide inventory animations in milliseconds
    float ScrollDisplayTimepan = 600; //Time to fade scroll menu animations in milliseconds
};
