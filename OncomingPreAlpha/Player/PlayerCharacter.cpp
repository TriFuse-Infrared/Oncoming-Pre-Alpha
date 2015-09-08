/*
 
 ____________   ______   ____________   _________  ___      ___   ______   ______
 |____   ____| |  ___ \  |____   ____| |  _______| |  |    |  |  /  ____|  |  ___|
      |  |     | |___) |      |  |     |  |        |  |    |  | |  |       |  |
      |  |     |    __/       |  |     |  |______  |  |    |  |  \  \___   |  |___
      |  |     |  _ \         |  |     |  _______| |  |    |  |   \__   \  |  ___|
      |  |     | | \ \        |  |     |  |        |  |    |  |      \   | |  |
      |  |     | |  \ \   ____|  |___  |  |         \  \__/  /   ____/  /  |  |___
      |__|     |_|   \_\ |___________| |__|          \______/    |_____/   |_____|
 
 
 
 -----------------------------------------------------------------------------------
 
 
 
 Oncoming Player Code - Written by AidoP, Property of Trifuse
 
 Description - Player controll code. This is reponsible for all interactions between the ingame player and its controller & environment.
 
 
 
 This code is not intended for public viewing to prevent errors being exploited. A censored version is avaliable for public use.
 
 */

#include "OncomingPreAlpha.h"
#include "PlayerCharacter.h"
#include "OncomingGameInstance.h"
#include "Item/Item.h"
#include "InventoryComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter(const class FObjectInitializer& PCIP) : Super() {
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    CreateComponentFromTemplate(NewObject<UInventoryComponent>());
    GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
    
    selectedQuickSlot = Primary;
    
    Utils = Utilities();
}

UItemRegistry* registry;

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
    Super::BeginPlay();
    
    
    //UInventoryComponent
    
    UOncomingGameInstance* inst = Cast<UOncomingGameInstance>(GetGameInstance());
    if(inst) {
        registry = inst->ItemRegistry;
    }
    UWorld* world = GetWorld();
    if (world) {
        //AItem* item = Cast<AItem>(world->SpawnActor(AItem::StaticClass()));
        //item->Name = "Used 0 times!";
        //Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0])->PrimarySlot = item;
    }
    
}

bool shouldDelayScrollToggleThisTick = false;
bool bScrolledLastTick = false;

// Called every frame
void APlayerCharacter::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    
    if(!shouldDelayScrollToggleThisTick) bScrolledLastTick = false;
    else shouldDelayScrollToggleThisTick = false;
}

void APlayerCharacter::OnLanded(const FHitResult &Hit) {
    
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
    Super::SetupPlayerInputComponent(InputComponent);
    
    check(InputComponent);
    
    //Movement Events
    InputComponent->BindAxis("VerticalStrafe", this, &APlayerCharacter::VerticalStrafeMovement);
    InputComponent->BindAxis("HorizontalStrafe", this, &APlayerCharacter::HorizontalStrafeMovement);
    InputComponent->BindAxis("Vertical", this, &APlayerCharacter::VerticalMovement);
    InputComponent->BindAxis("Horizontal", this, &APlayerCharacter::HorizontalMovement);
    InputComponent->BindAction("ScrollUp", IE_Pressed, this, &APlayerCharacter::ScrollUp);
    InputComponent->BindAction("ScrollDown", IE_Pressed, this, &APlayerCharacter::ScrollDown);
    InputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::CrouchPress);
    InputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::CrouchRelease);
    InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::SprintPress);
    InputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::SprintRelease);
    InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpPress);
    InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpRelease);
    
    //Inventory Events
    InputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::InventoryPress);
    InputComponent->BindAction("Inventory", IE_Released, this, &APlayerCharacter::InventoryRelease);
    InputComponent->BindAction("ClothingInventory", IE_Pressed, this, &APlayerCharacter::ClothingInventoryPress);
    InputComponent->BindAction("ClothingInventory", IE_Released, this, &APlayerCharacter::ClothingInventoryRelease);
    InputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);
    InputComponent->BindAction("Select", IE_Pressed, this, &APlayerCharacter::Select);
    InputComponent->BindAction("Drop", IE_Pressed, this, &APlayerCharacter::Drop);
    
    //Use Events
    InputComponent->BindAction("Primary", IE_Pressed, this, &APlayerCharacter::PrimaryPress);
    InputComponent->BindAction("Primary", IE_Released, this, &APlayerCharacter::PrimaryRelease);
    InputComponent->BindAction("Secondary", IE_Pressed, this, &APlayerCharacter::SecondaryPress);
    InputComponent->BindAction("Secondary", IE_Released, this, &APlayerCharacter::SecondaryRelease);
    InputComponent->BindAction("Tertiary", IE_Pressed, this, &APlayerCharacter::TertiaryPress);
    InputComponent->BindAction("Tertiary", IE_Released, this, &APlayerCharacter::TertiaryRelease);
    
    //Clothing Use Events
    InputComponent->BindAction("PrimaryClothing", IE_Pressed, this, &APlayerCharacter::PrimaryClothingPress);
    InputComponent->BindAction("PrimaryClothing", IE_Released, this, &APlayerCharacter::PrimaryClothingRelease);
    InputComponent->BindAction("SecondaryClothing", IE_Pressed, this, &APlayerCharacter::SecondaryClothingPress);
    InputComponent->BindAction("SecondaryClothing", IE_Released, this, &APlayerCharacter::SecondaryClothingRelease);
    InputComponent->BindAction("TertiaryClothing", IE_Pressed, this, &APlayerCharacter::TertiaryClothingPress);
    InputComponent->BindAction("TertiaryClothing", IE_Released, this, &APlayerCharacter::TertiaryClothingRelease);
    InputComponent->BindAction("QuaternaryClothing", IE_Pressed, this, &APlayerCharacter::QuaternaryClothingPress);
    InputComponent->BindAction("QuaternaryClothing", IE_Released, this, &APlayerCharacter::QuaternaryClothingRelease);
    InputComponent->BindAction("QuinaryClothing", IE_Pressed, this, &APlayerCharacter::QuinaryClothingPress);
    InputComponent->BindAction("QuinaryClothing", IE_Released, this, &APlayerCharacter::QuinaryClothingRelease);
    
}

//Movement events.

void APlayerCharacter::VerticalMovement(float Value) {
    AddControllerPitchInput(Value * mouseSensitivity * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::HorizontalMovement(float Value) {
    AddControllerYawInput(Value * mouseSensitivity * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::VerticalStrafeMovement(float Value) {
    AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::HorizontalStrafeMovement(float Value) {
    AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::ScrollUp() {
    if(!isInventoryOpen() && !isClothingInventoryOpen()) {
        if(selectedQuickSlot == Primary) {
            selectedQuickSlot = Secondary;
        } else if(selectedQuickSlot == Secondary) {
            selectedQuickSlot = Tertiary;
        } else if (selectedQuickSlot == Tertiary) {
            selectedQuickSlot = Primary;
        }
    }
    ScrollDirection = Up;
    shouldDelayScrollToggleThisTick = true;
    bScrolledLastTick = true;
}

void APlayerCharacter::ScrollDown() {
    if(!isInventoryOpen() && !isClothingInventoryOpen()) {
        if(selectedQuickSlot == Primary) {
            selectedQuickSlot = Tertiary;
        } else if(selectedQuickSlot == Secondary) {
            selectedQuickSlot = Primary;
        } else if (selectedQuickSlot == Tertiary) {
            selectedQuickSlot = Secondary;
        }
    }
    ScrollDirection = Down;
    shouldDelayScrollToggleThisTick = true;
    bScrolledLastTick = true;
}

void APlayerCharacter::JumpPress() {
    Jump();
}

void APlayerCharacter::JumpRelease() {
    StopJumping();
}

void APlayerCharacter::CrouchPress() {
    Crouch();
}

void APlayerCharacter::CrouchRelease() {
    UnCrouch();
}

void APlayerCharacter::SprintPress() {
    setSprinting(true);
}

void APlayerCharacter::SprintRelease() {
    setSprinting(false);
}

//Inventory events.

void APlayerCharacter::InventoryPress() {
    setInventoryOpen(true);
}

void APlayerCharacter::InventoryRelease() {
    setInventoryOpen(false);
}

void APlayerCharacter::ClothingInventoryPress() {
    setClothingInventoryOpen(true);
}

void APlayerCharacter::ClothingInventoryRelease() {
    setClothingInventoryOpen(false);
}

void APlayerCharacter::Reload() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    if(selectedQuickSlot == Primary) inv->PrimarySlot->Reload(this);
    if(selectedQuickSlot == Secondary) inv->SecondarySlot->Reload(this);
    if(selectedQuickSlot == Tertiary) inv->TertiarySlot->Reload(this);
}

void APlayerCharacter::Select() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    bool swapped = false;
    if(isInventoryOpen() || isClothingInventoryOpen()) {
        if(!(SelectedItem <= -11) && !(HoveredIndex <= -11)) {
            inv->SwapIndexes(SelectedItem, HoveredIndex);
            swapped = true;
        }
    }
    
    if (SelectedItem == -11) SelectedItem = HoveredIndex;
    if (swapped) SelectedItem = -11;
}

void APlayerCharacter::Drop() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    
}

//Use events.
void APlayerCharacter::PrimaryPress() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(selectedQuickSlot == Primary)    if(inv->PrimarySlot)    inv->PrimarySlot->PrimaryPress(this);
    if(selectedQuickSlot == Secondary)  if(inv->SecondarySlot)  inv->SecondarySlot->PrimaryPress(this);
    if(selectedQuickSlot == Tertiary)   if(inv->TertiarySlot)   inv->TertiarySlot->PrimaryPress(this);
}

void APlayerCharacter::PrimaryRelease() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(selectedQuickSlot == Primary)    if(inv->PrimarySlot)    inv->PrimarySlot->PrimaryRelease(this);
    if(selectedQuickSlot == Secondary)  if(inv->SecondarySlot)  inv->SecondarySlot->PrimaryRelease(this);
    if(selectedQuickSlot == Tertiary)   if(inv->TertiarySlot)   inv->TertiarySlot->PrimaryRelease(this);
}

void APlayerCharacter::SecondaryPress() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(selectedQuickSlot == Primary)    if(inv->PrimarySlot)    inv->PrimarySlot->SecondaryPress(this);
    if(selectedQuickSlot == Secondary)  if(inv->SecondarySlot)  inv->SecondarySlot->SecondaryPress(this);
    if(selectedQuickSlot == Tertiary)   if(inv->TertiarySlot)   inv->TertiarySlot->SecondaryPress(this);
}

void APlayerCharacter::SecondaryRelease() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(selectedQuickSlot == Primary)    if(inv->PrimarySlot)    inv->PrimarySlot->SecondaryRelease(this);
    if(selectedQuickSlot == Secondary)  if(inv->SecondarySlot)  inv->SecondarySlot->SecondaryRelease(this);
    if(selectedQuickSlot == Tertiary)   if(inv->TertiarySlot)   inv->TertiarySlot->SecondaryRelease(this);
}

void APlayerCharacter::TertiaryPress() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(selectedQuickSlot == Primary)    if(inv->PrimarySlot)    inv->PrimarySlot->TertiaryPress(this);
    if(selectedQuickSlot == Secondary)  if(inv->SecondarySlot)  inv->SecondarySlot->TertiaryPress(this);
    if(selectedQuickSlot == Tertiary)   if(inv->TertiarySlot)   inv->TertiarySlot->TertiaryPress(this);
}

void APlayerCharacter::TertiaryRelease() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(selectedQuickSlot == Primary)    if(inv->PrimarySlot)    inv->PrimarySlot->TertiaryRelease(this);
    if(selectedQuickSlot == Secondary)  if(inv->SecondarySlot)  inv->SecondarySlot->TertiaryRelease(this);
    if(selectedQuickSlot == Tertiary)   if(inv->TertiarySlot)   inv->TertiarySlot->TertiaryRelease(this);
}

//Clothing use events.

void APlayerCharacter::PrimaryClothingPress() {
    
}

void APlayerCharacter::PrimaryClothingRelease() {
    
}

void APlayerCharacter::SecondaryClothingPress() {
    
}

void APlayerCharacter::SecondaryClothingRelease() {
    
}

void APlayerCharacter::TertiaryClothingPress() {
    
}

void APlayerCharacter::TertiaryClothingRelease() {
    
}

void APlayerCharacter::QuaternaryClothingPress() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(inv->Bag)    inv->Bag->QuaternaryClothingPress(this);
}

void APlayerCharacter::QuaternaryClothingRelease() {
    UInventoryComponent* inv = Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    if(inv->Bag)    inv->Bag->QuaternaryClothingRelease(this);
}

void APlayerCharacter::QuinaryClothingPress() {
    
}

void APlayerCharacter::QuinaryClothingRelease() {
    
}


bool APlayerCharacter::isScrolling() const {
    return bScrolledLastTick;
}



bool APlayerCharacter::isScoping() const {
    return bIsScoping;
}

bool APlayerCharacter::isSprinting() const {
    return bIsSprinting;
}

bool APlayerCharacter::isInventoryOpen() const {
    return bIsInventoryOpen;
}

bool APlayerCharacter::isClothingInventoryOpen() const {
    return bIsClothingInventoryOpen;
}



void APlayerCharacter::setScoping(bool isScoping) {
    bIsScoping = isScoping;
    UpdateSpeed();
}

void APlayerCharacter::setSprinting(bool isSprinting) {
    bIsSprinting = isSprinting;
    UpdateSpeed();
}

void APlayerCharacter::setInventoryOpen(bool isInventoryOpen) {
    bIsInventoryOpen = isInventoryOpen;
    UpdateSpeed();
}

void APlayerCharacter::setClothingInventoryOpen(bool isClothingInventoryOpen) {
    bIsClothingInventoryOpen = isClothingInventoryOpen;
    UpdateSpeed();
}



void APlayerCharacter::UpdateSpeed() const {
    float maxSpeed = baseMovementSpeed;
    if(isScoping()) {
        maxSpeed *= scopingSpeedModifier;
    } if(isSprinting()) {
        maxSpeed *= sprintingSpeedModifier;
    } if(isInventoryOpen() || isClothingInventoryOpen()) {
        maxSpeed *= inventoryOpenSpeedModifier;
    }
    
    UInventoryComponent* inv =  Cast<UInventoryComponent>(GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    if(inv->GetWeight() >0) {
        //maxSpeed *= 1 / (inv->GetWeight() * 0.01); // NEED FORMULA
    }
    
    GetCharacterMovement()->MaxWalkSpeed = maxSpeed;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 0.5 * maxSpeed;
}









/* 
    Utilities Class!
 
    This class provides all the wrapper functions useful to both the Trifuse team, and mod developers!
*/


APlayerCharacter::Utilities::Utilities() {
    UE_LOG(OncomingOutput, Warning, TEXT("LOADED!"))
}

FVector APlayerCharacter::Utilities::GetPosition() {
    return FVector(0, 0, 0);
}


    
