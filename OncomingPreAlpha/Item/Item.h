// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Player/PlayerCharacter.h"
#include "Item.generated.h"

UCLASS()
class ONCOMINGPREALPHA_API AItem : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:

    enum ItemState {
        Inventory = 0,
        World = 1
    };
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    // For setting up the model
    virtual void InitMesh(FVector offset, UMeshComponent* mesh);
    
    // Keep track of where the item is to stop the game from fucking up
    virtual void SetState(ItemState state);
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    virtual void PrimaryPress(APlayerCharacter* player);                //Main Attack
    virtual void PrimaryRelease(APlayerCharacter* player);
    virtual void SecondaryPress(APlayerCharacter* player);              //Scopes/Charged Attack
    virtual void SecondaryRelease(APlayerCharacter* player);
    virtual void TertiaryPress(APlayerCharacter* player);               //Special Attack or Move. Ex. Gun-Hit with tailbutt (Or stabilise while scoped!), Medical-Heal team mate, Knife-Throw.
    virtual void TertiaryRelease(APlayerCharacter* player);
    
    virtual void Reload(APlayerCharacter* player);
    
    virtual void PrimaryClothingPress(APlayerCharacter* player);        //Hats
    virtual void PrimaryClothingRelease(APlayerCharacter* player);
    virtual void SecondaryClothingPress(APlayerCharacter* player);      //Shirts
    virtual void SecondaryClothingRelease(APlayerCharacter* player);
    virtual void TertiaryClothingPress(APlayerCharacter* player);       //Bags/Vests
    virtual void TertiaryClothingRelease(APlayerCharacter* player);
    virtual void QuaternaryClothingPress(APlayerCharacter* player);     //Pants
    virtual void QuaternaryClothingRelease(APlayerCharacter* player);
    virtual void QuinaryClothingPress(APlayerCharacter* player);        //Shoes
    virtual void QuinaryClothingRelease(APlayerCharacter* player);
    
    FString Name;
    FString Description;
    float Weight;           //Weight (Loosely based off kilos!)
    
    FString GetName();
    FString GetDescription();
    float GetWeight();
    
    UPROPERTY()
    UTexture2D* Icon; // Should be 200x200px
    
    UMeshComponent* Mesh;
};
