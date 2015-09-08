// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Item/Clothing/ClothingItem.h"
#include "Item/Clothing/HatItem.h"
#include "Item/Clothing/ShirtItem.h"
#include "Item/Clothing/BagItem.h"
#include "Item/Clothing/VestItem.h"
#include "Item/Clothing/PantsItem.h"
#include "Item/Clothing/ShoeItem.h"
#include "Item/Ingame/JetpackItem.h"
#include "Item/Throwable/Food/LumpyPorridge.h"
#include "Item/Clothing/AccessoryItem.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONCOMINGPREALPHA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    
    //Clothing the player is wearing. (Contains storage!)
    AHatItem* Hat;
    AShirtItem* Shirt;
    ABagItem* Bag;
    AVestItem* Vest;
    APantsItem* Pants;
    AShoeItem* Shoes;
    
    //No storage, but still amazing
    AAccessoryItem* Accessory;
    
    //Hand slots.
    AItem* PrimarySlot;
    AItem* SecondarySlot;
    AItem* TertiarySlot;
	
    float GetWeight() const;
    
    AItem* GetFromIndex(int Index);
    void SetFromIndex(int Index, AItem* Item);
    void SwapIndexes(int IndexA, int IndexB);
    
    int CalculateSize();
};
