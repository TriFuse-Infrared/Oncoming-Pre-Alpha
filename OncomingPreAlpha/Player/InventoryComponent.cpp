// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingPreAlpha.h"
#include "InventoryComponent.h"
#include "OncomingGameInstance.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    bWantsInitializeComponent = true;
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInventoryComponent::InitializeComponent() {
    Super::InitializeComponent();
    UWorld* world = GetWorld();
    if(world) {
        UOncomingGameInstance* inst = Cast<UOncomingGameInstance>(GetOwner()->GetGameInstance());
        if(inst) {
        }
        
        PrimarySlot = Cast<AItem>(world->SpawnActor<AItem>());
        SecondarySlot = world->SpawnActor<ALumpyPorridge>();
        TertiarySlot = Cast<AItem>(world->SpawnActor<AClothingItem>());
        
        GetOwner()->AttachRootComponentToActor(SecondarySlot);
        
        Hat = Cast<AHatItem>(world->SpawnActor<AHatItem>());
        Shirt = Cast<AShirtItem>(world->SpawnActor<AShirtItem>());
        Vest = Cast<AVestItem>(world->SpawnActor<AVestItem>());
        Bag = Cast<ABagItem>(world->SpawnActor<ABagItem>());
        Pants = Cast<APantsItem>(world->SpawnActor<APantsItem>());
        Shoes = Cast<AShoeItem>(world->SpawnActor<AShoeItem>());
        
        Hat->AddToStorage(world->SpawnActor<AAccessoryItem>());
        
        Accessory = Cast<AAccessoryItem>(world->SpawnActor<AAccessoryItem>());
    }
}

// Called every frame
void UInventoryComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

float UInventoryComponent::GetWeight() const {
    
    if(Hat)     Hat->UpdateWeight();
    if(Shirt)   Shirt->UpdateWeight();
    if(Vest)    Vest->UpdateWeight();
    if(Bag)     Bag->UpdateWeight();
    if(Pants)   Pants->UpdateWeight();
    if(Shoes)   Shoes->UpdateWeight();
    
    float weights = 0;
    
    if(PrimarySlot)     weights += PrimarySlot->GetWeight();
    if(SecondarySlot)   weights += SecondarySlot->GetWeight();
    if(TertiarySlot)    weights += TertiarySlot->GetWeight();
    
    if(Hat)             weights += Hat->Weight;
    if(Shirt)           weights += Shirt->Weight;
    if(Vest)            weights += Vest->Weight;
    if(Bag)             weights += Bag->Weight;
    if(Pants)           weights += Pants->Weight;
    if(Shoes)           weights += Shoes->Weight;
    
    if(Accessory)       weights += Accessory->Weight;
    
    return weights;
}


AItem* UInventoryComponent::GetFromIndex(int Index) {
    
    if(Index < 0) {
        
        if(Index == -10)      return Accessory;
        else if(Index == -9)  return Shoes;
        else if(Index == -8)  return Pants;
        else if(Index == -7)  return Bag;
        else if(Index == -6)  return Vest;
        else if(Index == -5)  return Shirt;
        else if(Index == -4)  return Hat;
        
        else if(Index == -3)  return TertiarySlot;
        else if(Index == -2)  return SecondarySlot;
        else if(Index == -1)  return PrimarySlot;
        
        return NULL;
    } else {
        
        int hatSize =   Hat     ? Hat->Storage.Num()    : 0;
        int shirtSize = Shirt   ? Shirt->Storage.Num()  : 0;
        int vestSize =  Vest    ? Vest->Storage.Num()   : 0;
        int bagSize =   Bag     ? Bag->Storage.Num()    : 0;
        int pantsSize = Pants   ? Pants->Storage.Num()  : 0;
        int shoesSize = Shoes   ? Shoes->Storage.Num()  : 0;
        
        if (Index < hatSize) {
            return Hat ? Hat->Storage[Index] : NULL;
        } else if (Index < hatSize + shirtSize) {
            Index -= hatSize;
            return Shirt ? Shirt->Storage[Index] : NULL;
        } else if (Index < hatSize + shirtSize + vestSize) {
            Index -= hatSize + shirtSize;
            return Vest ? Vest->Storage[Index] : NULL;
        } else if (Index < hatSize + shirtSize + vestSize + bagSize) {
            Index -= hatSize + shirtSize + vestSize;
            return Bag ? Bag->Storage[Index] : NULL;
        } else if (Index < hatSize + shirtSize + vestSize + bagSize + pantsSize) {
            Index -= hatSize + shirtSize + vestSize + bagSize;
            return Pants ? Pants->Storage[Index] : NULL;
        } else if (Index < hatSize + shirtSize + vestSize + bagSize + pantsSize + shoesSize) {
            Index -= hatSize + shirtSize + vestSize + bagSize + pantsSize;
            return Shoes ? Shoes->Storage[Index] : NULL;
        } else {
            return NULL;
        }
    }
}

void UInventoryComponent::SetFromIndex(int Index, AItem* Item) {
    
    if(Index < 0) {
        if(Index == -10 && Item->isAccessory)   Accessory = Cast<AAccessoryItem>(Item);
        
        if(Index == -9 && Item->isShoes)        Shoes   = Cast<AShoeItem>(Item);
        else if(Index == -8 && (!Item || Item->isPants))   Pants   = Cast<APantsItem>(Item);
        else if(Index == -7 && (!Item || Item->isShoes))   Bag   = Cast<ABagItem>(Item);
        else if(Index == -6 && (!Item || Item->isVest))    Vest   = Cast<AVestItem>(Item);
        else if(Index == -5 && (!Item || Item->isShirt))   Shirt   = Cast<AShirtItem>(Item);
        else if(Index == -4 && (!Item || Item->isHat))     Hat   = Cast<AHatItem>(Item);
        
        if(Index == -3)         TertiarySlot  = Item;
        else if(Index == -2)    SecondarySlot = Item;
        else if(Index == -1)    PrimarySlot   = Item;
        
        return;
    }
    
    else {
        
        int hatSize =   Hat     ? Hat->Storage.Num()    : 0;
        int shirtSize = Shirt   ? Shirt->Storage.Num()  : 0;
        int vestSize =  Vest    ? Vest->Storage.Num()   : 0;
        int bagSize =   Bag     ? Bag->Storage.Num()    : 0;
        int pantsSize = Pants   ? Pants->Storage.Num()  : 0;
        int shoesSize = Shoes   ? Shoes->Storage.Num()  : 0;
        
        if (Index < hatSize) {
            Hat->Storage[Index] = Item;
        } else if (Index < hatSize + shirtSize) {
            Shirt->Storage[Index] = Item;
            Index -= hatSize;
        } else if (Index < hatSize + shirtSize + vestSize) {
            Vest->Storage[Index] = Item;
            Index -= hatSize + shirtSize;
        } else if (Index < hatSize + shirtSize + vestSize + bagSize) {
            Bag->Storage[Index] = Item;
            Index -= hatSize + shirtSize + vestSize;
        } else if (Index < hatSize + shirtSize + vestSize + bagSize + pantsSize) {
            Pants->Storage[Index] = Item;
            Index -= hatSize + shirtSize + vestSize + bagSize;
        } else if (Index < hatSize + shirtSize + vestSize + bagSize + pantsSize + shoesSize) {
            Shoes->Storage[Index] = Item;
            Index -= hatSize + shirtSize + vestSize + bagSize + pantsSize;
        }
    }
}

void UInventoryComponent::SwapIndexes(int IndexA, int IndexB) {
    if(IndexA <= -11 || IndexB <= -11) return;
    
    AItem* a;
    AItem* b;
    
    a = GetFromIndex(IndexA);
    b = GetFromIndex(IndexB);
    
    if (a) if(b) UE_LOG(OncomingOutput, Warning, TEXT("a = %s  : b = %s"), *(a->Name), *(b->Name));
    
    SetFromIndex(IndexA, b);
    SetFromIndex(IndexB, a);
}

int UInventoryComponent::CalculateSize() {
    int hat = Hat->Storage.Num();
    int shirt = Shirt->Storage.Num();
    int vest = Vest->Storage.Num();
    int bag = Bag->Storage.Num();
    int pants = Pants->Storage.Num();
    int shoes = Shoes->Storage.Num();
    
    return hat + shirt + vest + bag + pants + shoes;
}