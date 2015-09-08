// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

enum QuickSlot {
    Primary = 1,
    Secondary = 2,
    Tertiary = 3
};

enum ScrollDirection {
    Up = 1,
    Down = 2
};

UCLASS()
class ONCOMINGPREALPHA_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()
    
public:
    // Sets default values for this character's properties
    APlayerCharacter(const class FObjectInitializer& PCIP);
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called when player lands
    virtual void OnLanded(const FHitResult& Hit) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    void VerticalMovement(float Value);
    void HorizontalMovement(float Value);
    void VerticalStrafeMovement(float Value);
    void HorizontalStrafeMovement(float Value);
    void ScrollUp();
    void ScrollDown();
    
    void PrimaryPress();                //Main Attack
    void PrimaryRelease();
    void SecondaryPress();              //Scopes/Charged Attack
    void SecondaryRelease();
    void TertiaryPress();               //Special Attack or Move. Ex. Gun-Hit with tailbutt (Or stabilise while scoped!), Medical-Heal team mate, Knife or can of food-Throw.
    void TertiaryRelease();
    
    void PrimaryClothingPress();        //Hats
    void PrimaryClothingRelease();
    void SecondaryClothingPress();      //Shirts
    void SecondaryClothingRelease();
    void TertiaryClothingPress();       //Bags/Vests
    void TertiaryClothingRelease();
    void QuaternaryClothingPress();     //Pants
    void QuaternaryClothingRelease();
    void QuinaryClothingPress();        //Shoes
    void QuinaryClothingRelease();
    
    void JumpPress();
    void JumpRelease();
    void CrouchPress();
    void CrouchRelease();
    void PausePress();
    void PauseRelease();
    void SprintPress();
    void SprintRelease();
    
    void InventoryPress();
    void InventoryRelease();
    void ClothingInventoryPress();
    void ClothingInventoryRelease();
    void Reload();
    void Select();
    void Drop();
    
    bool isScrolling() const;
    
    bool isScoping() const;
    bool bIsScoping = false;
    bool isSprinting() const;
    bool bIsSprinting = false;
    bool isInventoryOpen() const;
    bool isClothingInventoryOpen() const;
    bool bIsInventoryOpen = false;
    bool bIsClothingInventoryOpen = false;
    
    void setScoping(bool isScoping);
    void setSprinting(bool isSprinting);
    void setInventoryOpen(bool isInventoryOpen);
    void setClothingInventoryOpen(bool isClothingInventoryOpen);
    
    void UpdateSpeed() const;
    
    const float baseMovementSpeed = 600;
    float scopingSpeedModifier = 0.5;
    float sprintingSpeedModifier = 1.8;
    float inventoryOpenSpeedModifier = 0.6;
    float weightThreshold = 5;
    
    float mouseSensitivity = 150;
    
    QuickSlot selectedQuickSlot = Primary;
    int SelectedItem = -11;
    int HoveredIndex = -11;
    
    ScrollDirection ScrollDirection = Up;
    
    
    class Utilities {
    public:
        APlayerCharacter* player;
        
        Utilities(APlayerCharacter* player);
        
        FVector GetPosition();
        FVector GetForwards();
    };
    
    Utilities Utils;
    
};

