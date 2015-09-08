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
 
 
 
 Oncoming HUD Code - Written by AidoP, Property of Trifuse
 
 Description - HUD Display, Shows player's health etc, but also inventory and other 2d displays
 
*/



#include "OncomingPreAlpha.h"
#include "InventoryComponent.h"
#include "IngameHUD.h"


FVector2D ScreenSize;

int QuickSlotOpacity = 0;

float InventoryPosX = ScreenSize.X;
float ClothingInventoryPosX = ScreenSize.X;


// Initialiser - Run once when the class is created
AIngameHUD::AIngameHUD(const FObjectInitializer& ObjIntializer) : Super(ObjIntializer) {
    
    // Create Font
    static ConstructorHelpers::FObjectFinder<UFont> AudiowideObj (TEXT("/Game/HUD/Audiowide")); // Get font from file
    Audiowide = AudiowideObj.Object; // Set font object from helper object
    static ConstructorHelpers::FObjectFinder<UFont> AudiowideSObj (TEXT("/Game/HUD/Audiowide14pt")); // Get font from file
    AudiowideSmall = AudiowideSObj.Object; // Set font object from helper object
    
    
    //Load item container textures
    static ConstructorHelpers::FObjectFinder<UTexture2D> ItemContainerObj(TEXT("/Game/HUD/ItemContainer")); // Get texture from file
    static ConstructorHelpers::FObjectFinder<UTexture2D> SelectedItemContainerObj(TEXT("/Game/HUD/SelectedItemContainer")); // Get texture from file
    
    ItemContainerTex = ItemContainerObj.Object; // Set texture object from helper object
    SelectedItemContainerTex = SelectedItemContainerObj.Object; // Set texture object from helper object
    
    ItemContainer = UCanvas::MakeIcon(ItemContainerTex); // Create and set icon object from texture object
    SelectedItemContainer = UCanvas::MakeIcon(SelectedItemContainerTex); // Create and set icon object from texture object
}


float InventoryLabelOpacity = 0; // Opacity of inventory labels
float InventoryOpenedTimespan = 0; // Time the inventory has been opened for
float InventoryClosedTimespan = 0; // Time the inventory has been closed for

float ClothingInventoryLabelOpacity = 0; // Opacity of clothing inventory labels
float ClothingInventoryOpenedTimespan = 0; // Time the clothing inventory has been opened for
float ClothingInventoryClosedTimespan = 0; // Time the clothing inventory has been closed for

float QuickSlotsLastShownTimespan = 0; // Time since the Quickslots were last shown

int selectedInventorySlot = 0; // Currently selected slot in the clothing inventory
int selectedClothingInventorySlot = 0; // Currently selected slot in the clothing inventory

float lastTickMS;
void AIngameHUD::DrawHUD() {
    
    // Update time stuff
    FDateTime now = FDateTime::Now(); // Get the current time
    float nowMS = ((now.GetHour() * 60 + now.GetMinute()) * 60 + now.GetSecond()) * 1000 + now.GetMillisecond(); // Get the current time in milliseconds
    float deltaTime = nowMS - lastTickMS;
    
    
    // Get player (And store to variable for easy access)
    APlayerCharacter* player = Cast<APlayerCharacter>(GetOwningPawn());
    if (!player) return; // Stop bad things from happening when (for whatever reason) the pointer to the player is NULL
    
    // Get inventory
    UInventoryComponent* inv = Cast<UInventoryComponent>(player->GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    
    // Get the current screen size
    if (!GEngine) return; // And why would GEngine ever be NULL? - Better safe than sorry anyhow
    ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY); // Set the screen size
    
    
    // Quick Slot scrolling logic & display
    QuickSlotsLastShownTimespan += deltaTime;
    
    if (player->isScrolling() && !player->isInventoryOpen() && !player->isClothingInventoryOpen()) { // Only when scrolling and when neither of the inventories are open
        QuickSlotsLastShownTimespan = 0; // Update time quickslots have been closed
    }
    
    // Calculate Opacity
    QuickSlotOpacity = FMath::Lerp(255, 0, FMath::Clamp(QuickSlotsLastShownTimespan / ScrollDisplayTimepan, 0.0f, 1.0f)); // Opacity = Lerp between timespan slots have been hidden / display timespan constant (Must be clamped between 0 and 1)
    
    // Draw the Quick Slots if not invisible
    if (QuickSlotOpacity > 0) {
        DrawQuickSlots(); // Draw the quick slots
    }
    
    // Inventory logic
    int InventorySize = inv->CalculateSize();
    
    if (player->isInventoryOpen() && !(ClothingInventoryPosX < ScreenSize.X)) { // Check if the inventory is open
        
        player->HoveredIndex = selectedInventorySlot; // Set the hovered index for item swaping
        
        InventoryClosedTimespan = 0; // Reset the amount of time the inventory has been closed
        
        InventoryOpenedTimespan += deltaTime; // Add the difference between ticks to the timespan
        
        InventoryPosX = FMath::Lerp(ScreenSize.X, ScreenSize.X - 100, FMath::Clamp(InventoryOpenedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate the x of the inventory by lerping between time open & slide transition time
        
        InventoryLabelOpacity = FMath::Lerp(0.0f, 1.0f, FMath::Clamp(InventoryOpenedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate label opacity
        
        // Scrolling logic
        if (player->isScrolling()) { // If the player is scrolling the mouse
            if (player->ScrollDirection == Up) selectedInventorySlot = selectedInventorySlot > 0 ? selectedInventorySlot - 1 : InventorySize; // If scrolling up, decrease the hovered index by 1. If the hovered index is 0, however, set it to the last slot
            if (player->ScrollDirection == Down) selectedInventorySlot = selectedInventorySlot < InventorySize ? selectedInventorySlot + 1 : 0; // The opposite of above
        }
    }
    
    else { // When the inventory is not open
        
        InventoryOpenedTimespan = 0; // Reset the amount of time the inventory has been open
    
        InventoryClosedTimespan += deltaTime; // Add the difference between ticks to the timespan
        
        InventoryPosX = FMath::Lerp(ScreenSize.X - 100, ScreenSize.X, FMath::Clamp(InventoryClosedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate the x of the inventory by lerping between time open & slide transition time
        
        InventoryLabelOpacity = FMath::Lerp(1.0f, 0.0f, FMath::Clamp(InventoryClosedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate label opacity
    }
    
    if (InventoryPosX < ScreenSize.X) { // When part of the inventory is visible
        DrawInventory(); // Draw the inventory
    }
    
    // Clothing Inventory logic
    int ClothingInventorySize = 10; // Size of the clothing inventory - Clothes, Accessory & Quick slots (So you can swap items!)
    
    if (player->isClothingInventoryOpen() && !(InventoryPosX < ScreenSize.X)) { // Check if the inventory is open
        
        player->HoveredIndex = ConvertClothingSlot(selectedClothingInventorySlot); // Set the hovered index for item swaping
        
        ClothingInventoryClosedTimespan = 0; // Reset the amount of time the inventory has been closed
        
        ClothingInventoryOpenedTimespan += deltaTime; // Add the difference between ticks to the timespan
        
        ClothingInventoryPosX = FMath::Lerp(ScreenSize.X, ScreenSize.X - 100, FMath::Clamp(ClothingInventoryOpenedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate the x of the inventory by lerping between time open & slide transition time
        
        ClothingInventoryLabelOpacity = FMath::Lerp(0.0f, 1.0f, FMath::Clamp(ClothingInventoryOpenedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate label opacity
        
        // Scrolling logic
        if (player->isScrolling()) { // If the player is scrolling the mouse
            if (player->ScrollDirection == Up) selectedClothingInventorySlot = selectedClothingInventorySlot > 0 ? selectedClothingInventorySlot - 1 : ClothingInventorySize - 1; // If scrolling up, decrease the hovered index by 1. If the hovered index is 0, however, set it to the last slot
            if (player->ScrollDirection == Down) selectedClothingInventorySlot = selectedClothingInventorySlot < ClothingInventorySize - 1 ? selectedClothingInventorySlot + 1 : 0; // The opposite of above
        }
    }
    
    else { // When the inventory is not open
        
        ClothingInventoryOpenedTimespan = 0; // Reset the amount of time the inventory has been open
        
        ClothingInventoryClosedTimespan += deltaTime; // Add the difference between ticks to the timespan
        
        ClothingInventoryPosX = FMath::Lerp(ScreenSize.X - 100, ScreenSize.X, FMath::Clamp(ClothingInventoryClosedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate the x of the inventory by lerping between time open & slide transition time
        
        ClothingInventoryLabelOpacity = FMath::Lerp(1.0f, 0.0f, FMath::Clamp(ClothingInventoryClosedTimespan / InventorySlideTimespan, 0.0f, 1.0f)); // Calculate label opacity
    }
    
    if (ClothingInventoryPosX < ScreenSize.X) { // When part of the inventory is visible
        DrawClothingInventory(); // Draw the inventory
    }
    
    if(InventoryPosX >= ScreenSize.X && ClothingInventoryPosX >= ScreenSize.X) player->HoveredIndex = -11;
    
    // Draw the selected item, if there is one
    if(player->SelectedItem >= -10) DrawSelectedItem();
    
    // Time last tick - This should always be the last thing to change each frame
    lastTickMS = nowMS;
}

void AIngameHUD::DrawQuickSlots() {
    Canvas->DrawColor = FColor().White.WithAlpha(QuickSlotOpacity); // Set the draw colour
    
    // Get player (And store to variable for easy access)
    APlayerCharacter* player = Cast<APlayerCharacter>(GetOwningPawn());
    if (!player) return; // Stop bad things from happening when (for whatever reason) the pointer to the player is NULL
    
    // Get inventory
    UInventoryComponent* inv = Cast<UInventoryComponent>(player->GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    
    // Variables for the particular slots
    AItem* previousItem = NULL; // The slot before the selected one
    AItem* currentItem = NULL; // The currently selected slot
    AItem* nextItem = NULL; // The item after the selected slot
    
    FString name = ""; // The name to display for the selected slot
    
    if(player->selectedQuickSlot == Primary) {
        previousItem = inv->TertiarySlot;
        currentItem = inv->PrimarySlot;
        nextItem = inv->SecondarySlot;
        
        if(inv->PrimarySlot) name = inv->PrimarySlot->Name;
    }
    
    else if(player->selectedQuickSlot == Secondary) {
        previousItem = inv->PrimarySlot;
        currentItem = inv->SecondarySlot;
        nextItem = inv->TertiarySlot;
        
        if(inv->SecondarySlot) name = inv->SecondarySlot->Name;
    }
    
    else if(player->selectedQuickSlot == Tertiary) {
        previousItem = inv->SecondarySlot;
        currentItem = inv->TertiarySlot;
        nextItem = inv->PrimarySlot;
        
        if(inv->TertiarySlot) name = inv->TertiarySlot->Name;
    }
    
    // Draw the containers
    Canvas->DrawScaledIcon(Canvas->MakeIcon(ItemContainerTex)   , ScreenSize.X / 2 - 105, ScreenSize.Y / 2 + (150 / 2) + 30, FVector(0.5f, 0.5f, 0.5f)); //  Previous Icon container
    Canvas->DrawScaledIcon(Canvas->MakeIcon(ItemContainerTex)   , ScreenSize.X / 2 - (150 / 2), ScreenSize.Y / 2 - (150 / 2), FVector(0.75f, 0.75f, 0.75f)); // Current Icon container
    Canvas->DrawScaledIcon(Canvas->MakeIcon(ItemContainerTex)   , ScreenSize.X / 2 + 5, ScreenSize.Y / 2 + (150 / 2) + 30, FVector(0.5f, 0.5f, 0.5f)); // Next Icon Container
    
    // Draw the icons
    if(previousItem)    if(previousItem->Icon)  Canvas->DrawScaledIcon(Canvas->MakeIcon(Cast<UTexture>(previousItem->Icon)) , ScreenSize.X / 2 - 105, ScreenSize.Y / 2 + (150 / 2) + 30, FVector(0.5f, 0.5f, 0.5f)); // Previous Icon
    if(currentItem)     if(currentItem->Icon)   Canvas->DrawScaledIcon(Canvas->MakeIcon(Cast<UTexture>(currentItem->Icon))  , ScreenSize.X / 2 - (150 / 2), ScreenSize.Y / 2 - (150 / 2), FVector(0.75f, 0.75f, 0.75f)); // Current Icon
    if(nextItem)        if(nextItem->Icon)      Canvas->DrawScaledIcon(Canvas->MakeIcon(Cast<UTexture>(nextItem->Icon))     , ScreenSize.X / 2 + 5, ScreenSize.Y / 2 + (150 / 2) + 30, FVector(0.5f, 0.5f, 0.5f)); // Next Icon
    
    float sizeX, sizeY;
    Canvas->StrLen(AudiowideSmall, name, sizeX, sizeY);
    
    FCanvasTextItem itemLabel = FCanvasTextItem(FVector2D(0, 0), FText(FText::FromString("Item Name")), AudiowideSmall, FLinearColor(Canvas->DrawColor));
    
    itemLabel.Text = FText(FText::FromString(name));
    
    itemLabel.Position = FVector2D(ScreenSize.X / 2 - sizeX / 2, ScreenSize.Y / 2 + 150 / 2 + 3);
    
    itemLabel.ShadowColor = FColor::Black;
    itemLabel.ShadowOffset = FVector2D(1, 1);
    
    Canvas->DrawItem(itemLabel);
}

void AIngameHUD::DrawInventory() {
    
    // Get player (And store to variable for easy access)
    APlayerCharacter* player = Cast<APlayerCharacter>(GetOwningPawn());
    if (!player) return; // Stop bad things from happening when (for whatever reason) the pointer to the player is NULL
    
    // Get inventory
    UInventoryComponent* inv = Cast<UInventoryComponent>(player->GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    // Set the draw colour
    Canvas->DrawColor = FColor().White;
    
    // Draw inventory slots before the one getting hovered over
    for (int i = 1; i <= selectedInventorySlot; i++) {
        Canvas->DrawScaledIcon(ItemContainer, InventoryPosX + 5, ScreenSize.Y / 2 - 40 - 5 + (-85 * i), FVector(0.4f, 0.4f, 0.4f)); // Draw the container
        
        // Number label
        FString number = FString::FromInt(selectedInventorySlot - i); // Get number for the label, and cast it to an FString
        float numLSizeX = 0;
        float numLSizeY = 0;
        Canvas->StrLen(AudiowideSmall, number, numLSizeX, numLSizeY); // Calculate the size of the text label
        FLinearColor numLColour = FLinearColor(0.3, 0.3, 0.3); // Label colour
        numLColour.A = InventoryLabelOpacity; // Set colour opacity for animation
        FCanvasTextItem numberLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - numLSizeX, ScreenSize.Y / 2 - 5 - numLSizeY / 2 + (-85 * i)), FText::FromString(number), AudiowideSmall, numLColour); // Create label
        numberLabel.ShadowColor = FLinearColor(0, 0, 0); // Shadow color (Black)
        numberLabel.ShadowOffset = FVector2D(1, 1); // Shadow offset
        Canvas->DrawItem(numberLabel); // Draw Label
        
        AItem* item = inv->GetFromIndex(selectedInventorySlot - i); // Get the item to display - Reverse the order as we are going up not down
        if(item) { // Ensure the item exists
            if(item->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(item->Icon), InventoryPosX + 5, ScreenSize.Y / 2 - 40 - 5 + (-85 * i), FVector(0.4f, 0.4f, 0.4f)); // Draw the item icon (And check that it exists!)
        }
        
    }
    
    //Draw the currently hovered slot
    Canvas->DrawScaledIcon(SelectedItemContainer, InventoryPosX + 5, ScreenSize.Y / 2 - 40, FVector(0.4f, 0.4f, 0.4f));
    AItem* hoveredItem = inv->GetFromIndex(selectedInventorySlot); // Get the item to display
    if(hoveredItem) { // Ensure the item exists
        if(hoveredItem->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(hoveredItem->Icon), InventoryPosX + 5, ScreenSize.Y / 2 - 40, FVector(0.4f, 0.4f, 0.4f)); // Draw the item icon (And check that it exists!)
        
        // Draw item name, description and weight
        FString name = hoveredItem->Name; // Get the name
        FString desc = hoveredItem->Description; // Get the description
        FString weight = FString::SanitizeFloat(hoveredItem->Weight) + "kg"; // Get the weight of the item as an FString
        
        AClothingItem* clothItem = Cast<AClothingItem>(hoveredItem); // Cast to usable clothing item
        if(clothItem) weight =+ " (" + FString::FromInt(clothItem->CalculateStorageUsed()) + " / " + FString::FromInt(clothItem->Storage.Num()) + ")"; // Test that it was a clothing item then change weight label to show storage
        
        // Calculate label sizes
        float nameX, nameY; // Name label
        Canvas->StrLen(AudiowideSmall, name, nameX, nameY);
        
        float descX, descY; // Description label
        Canvas->StrLen(AudiowideSmall, desc, descX, descY);
        
        float weightX, weightY; // Weight label
        Canvas->StrLen(AudiowideSmall, weight, weightX, weightY);
        
        // Labels
        FLinearColor nameLabelColour = FLinearColor(1, 1, 1);
        nameLabelColour.A = InventoryLabelOpacity;
        FCanvasTextItem nameLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - nameX, ScreenSize.Y / 2 - 40), FText::FromString(name), AudiowideSmall,nameLabelColour); // Name label
        nameLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        nameLabel.ShadowOffset = FVector2D(1, 1);
        
        FLinearColor descLabelColour = FLinearColor(0.3, 0.3, 0.3);
        descLabelColour.A = InventoryLabelOpacity;
        FCanvasTextItem descLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - descX, ScreenSize.Y / 2 - 40 + 28), FText::FromString(desc), AudiowideSmall, descLabelColour); // Description label
        descLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        descLabel.ShadowOffset = FVector2D(1, 1);
        
        FLinearColor weightLabelColour = FLinearColor(0.5, 0.5, 0.5);
        weightLabelColour.A = InventoryLabelOpacity;
        FCanvasTextItem weightLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - weightX, ScreenSize.Y / 2 - 40 + 56), FText::FromString(weight), AudiowideSmall, weightLabelColour); // Weight label
        weightLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        weightLabel.ShadowOffset = FVector2D(1, 1);
        
        // Draw the labels
        Canvas->DrawItem(nameLabel); // Draw the name
        Canvas->DrawItem(descLabel); // Draw the description
        Canvas->DrawItem(weightLabel); // Draw the weight
    }
    
    // Draw inventory slots after the one getting hovered over
    for (int i = 1; i + selectedInventorySlot <= inv->CalculateSize(); i++) {
        // Draw the container
        Canvas->DrawScaledIcon(ItemContainer, InventoryPosX + 5, ScreenSize.Y / 2 + 40 + 5 + (85 * (i - 1)) , FVector(0.4f, 0.4f, 0.4f));
        
        // Number label
        FString number = FString::FromInt(selectedInventorySlot + i); // Get number for the label, and cast it to an FString
        float numLSizeX = 0;
        float numLSizeY = 0;
        Canvas->StrLen(AudiowideSmall, number, numLSizeX, numLSizeY); // Calculate the size of the text label
        FLinearColor numLColour = FLinearColor(0.3, 0.3, 0.3); // Label colour
        numLColour.A = InventoryLabelOpacity; // Set colour opacity for animation
        FCanvasTextItem numberLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - numLSizeX, ScreenSize.Y / 2 + 5 - numLSizeY / 2 + (85 * i)), FText::FromString(number), AudiowideSmall, numLColour); // Create label
        numberLabel.ShadowColor = FLinearColor(0, 0, 0); // Shadow color (Black)
        numberLabel.ShadowOffset = FVector2D(1, 1); // Shadow offset
        Canvas->DrawItem(numberLabel); // Draw Label
        
        AItem* item = inv->GetFromIndex(i + selectedInventorySlot); // Get the item to display
        if(item) { // Ensure the item exists
            if(item->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(item->Icon), InventoryPosX + 5, ScreenSize.Y / 2 + 40 + 5 + (85 * (i - 1)), FVector(0.4f, 0.4f, 0.4f)); // Draw the item icon (And check that it exists!)
        }
    }
}

void AIngameHUD::DrawClothingInventory() {
    
    // Get player (And store to variable for easy access)
    APlayerCharacter* player = Cast<APlayerCharacter>(GetOwningPawn());
    if (!player) return; // Stop bad things from happening when (for whatever reason) the pointer to the player is NULL
    
    // Get inventory
    UInventoryComponent* inv = Cast<UInventoryComponent>(player->GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    // Set the draw colour
    Canvas->DrawColor = FColor().White;
    
    int ClothingInventorySize = 10; // Size of the clothing inventory (Clothing, Quickslots & Accessory)
    
    // Array for easy index to item conversion
    TArray<AItem*> clothingInv;
    // Add item pointers to clothing inventory
    clothingInv.Add(inv->Hat);
    clothingInv.Add(inv->Shirt);
    clothingInv.Add(inv->Vest);
    clothingInv.Add(inv->Bag);
    clothingInv.Add(inv->Pants);
    clothingInv.Add(inv->Shoes);
    
    clothingInv.Add(inv->Accessory);
    
    clothingInv.Add(inv->PrimarySlot);
    clothingInv.Add(inv->SecondarySlot);
    clothingInv.Add(inv->TertiarySlot);
    
    // Draw items before the selected slot
    for (int i = 1; i <= selectedClothingInventorySlot; i++) {
        Canvas->DrawScaledIcon(ItemContainer, ClothingInventoryPosX + 5, ScreenSize.Y / 2 - 40 - 5 + (-85 * i), FVector(0.4f, 0.4f, 0.4f)); // Draw the container
        
        // Number label
        FString number = ConvertClothingIndexToName(selectedClothingInventorySlot - i); // Get number for the label, and cast it to an FString
        float numLSizeX = 0;
        float numLSizeY = 0;
        Canvas->StrLen(AudiowideSmall, number, numLSizeX, numLSizeY); // Calculate the size of the text label
        FLinearColor numLColour = FLinearColor(0.3, 0.3, 0.3); // Label colour
        numLColour.A = ClothingInventoryLabelOpacity; // Set colour opacity for animation
        FCanvasTextItem numberLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - numLSizeX, ScreenSize.Y / 2 - 5 - numLSizeY / 2 + (-85 * i)), FText::FromString(number), AudiowideSmall, numLColour); // Create label
        numberLabel.ShadowColor = FLinearColor(0, 0, 0); // Shadow color (Black)
        numberLabel.ShadowOffset = FVector2D(1, 1); // Shadow offset
        Canvas->DrawItem(numberLabel); // Draw Label
        
        if(clothingInv[selectedClothingInventorySlot - i]) { // Check that the item exists
            if(clothingInv[selectedClothingInventorySlot - i]->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(clothingInv[selectedClothingInventorySlot - i]->Icon), ClothingInventoryPosX + 5, ScreenSize.Y / 2 - 40 - 5 + (-85 * i), FVector(0.4f, 0.4f, 0.4f));
        }
    }
    
    // Draw selected item
    Canvas->DrawScaledIcon(SelectedItemContainer, ClothingInventoryPosX + 5, ScreenSize.Y / 2 - 40, FVector(0.4f, 0.4f, 0.4f));
    
    if(clothingInv[selectedClothingInventorySlot]) { // Ensure the item exists
        if(clothingInv[selectedClothingInventorySlot]->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(clothingInv[selectedClothingInventorySlot]->Icon), ClothingInventoryPosX + 5, ScreenSize.Y / 2 - 40, FVector(0.4f, 0.4f, 0.4f)); // Draw the item icon (And check that it exists!)
        
        // Draw item name, description and weight
        FString name = clothingInv[selectedClothingInventorySlot]->Name; // Get the name
        FString desc = clothingInv[selectedClothingInventorySlot]->Description; // Get the description
        FString weight = FString::SanitizeFloat(clothingInv[selectedClothingInventorySlot]->Weight) + "kg"; // Get the weight of the item as an FString
        
        AClothingItem* clothItem = Cast<AClothingItem>(clothingInv[selectedClothingInventorySlot]); // Cast to usable clothing item
        if(clothItem) weight += " (" + FString::FromInt(clothItem->CalculateStorageUsed()) + "/" + FString::FromInt(clothItem->Storage.Num()) + ")"; // Test that it was a clothing item then change weight label to show storage
        
        // Calculate label sizes
        float nameX, nameY; // Name label
        Canvas->StrLen(AudiowideSmall, name, nameX, nameY);
        
        float descX, descY; // Description label
        Canvas->StrLen(AudiowideSmall, desc, descX, descY);
        
        float weightX, weightY; // Weight label
        Canvas->StrLen(AudiowideSmall, weight, weightX, weightY);
        
        // Labels
        FLinearColor nameLabelColour = FLinearColor(1, 1, 1);
        nameLabelColour.A = ClothingInventoryLabelOpacity;
        FCanvasTextItem nameLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - nameX, ScreenSize.Y / 2 - 40), FText::FromString(name), AudiowideSmall,nameLabelColour); // Name label
        nameLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        nameLabel.ShadowOffset = FVector2D(1, 1);
        
        FLinearColor descLabelColour = FLinearColor(0.3, 0.3, 0.3);
        descLabelColour.A = ClothingInventoryLabelOpacity;
        FCanvasTextItem descLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - descX, ScreenSize.Y / 2 - 40 + 28), FText::FromString(desc), AudiowideSmall, descLabelColour); // Description label
        descLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        descLabel.ShadowOffset = FVector2D(1, 1);
        
        FLinearColor weightLabelColour = FLinearColor(0.5, 0.5, 0.5);
        weightLabelColour.A = ClothingInventoryLabelOpacity;
        FCanvasTextItem weightLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - weightX, ScreenSize.Y / 2 - 40 + 56), FText::FromString(weight), AudiowideSmall, weightLabelColour); // Weight label
        weightLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        weightLabel.ShadowOffset = FVector2D(1, 1);
        
        // Draw the labels
        Canvas->DrawItem(nameLabel); // Draw the name
        Canvas->DrawItem(descLabel); // Draw the description
        Canvas->DrawItem(weightLabel); // Draw the weight
    }
    
    // Draw items after the selected slot
    for (int i = 1; i + selectedClothingInventorySlot <= ClothingInventorySize - 1; i++) {
        Canvas->DrawScaledIcon(ItemContainer, ClothingInventoryPosX + 5, ScreenSize.Y / 2 + 40 + 5 + (85 * (i - 1)) , FVector(0.4f, 0.4f, 0.4f)); // Draw the container
        
        // Number label
        FString number = ConvertClothingIndexToName(selectedClothingInventorySlot + i); // Get number for the label, and cast it to an FString
        float numLSizeX = 0;
        float numLSizeY = 0;
        Canvas->StrLen(AudiowideSmall, number, numLSizeX, numLSizeY); // Calculate the size of the text label
        FLinearColor numLColour = FLinearColor(0.3, 0.3, 0.3); // Label colour
        numLColour.A = ClothingInventoryLabelOpacity; // Set colour opacity for animation
        FCanvasTextItem numberLabel = FCanvasTextItem(FVector2D(ScreenSize.X - 100 - numLSizeX, ScreenSize.Y / 2 + 5 - numLSizeY / 2 + (85 * i)), FText::FromString(number), AudiowideSmall, numLColour); // Create label
        numberLabel.ShadowColor = FLinearColor(0, 0, 0); // Shadow color (Black)
        numberLabel.ShadowOffset = FVector2D(1, 1); // Shadow offset
        Canvas->DrawItem(numberLabel); // Draw Label
        
        if(clothingInv[selectedClothingInventorySlot + i]) { // Check that the item exists
            if(clothingInv[selectedClothingInventorySlot + i]->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(clothingInv[selectedClothingInventorySlot + i]->Icon), ClothingInventoryPosX + 5, ScreenSize.Y / 2 + 40 + 5 + (85 * (i - 1)), FVector(0.4f, 0.4f, 0.4f));
        }
    }
}

int AIngameHUD::ConvertClothingSlot(int slot) {
    if(slot == 0) return -4; // Hat
    if(slot == 1) return -5; // ...
    if(slot == 2) return -6;
    if(slot == 3) return -7;
    if(slot == 4) return -8; // ...
    if(slot == 5) return -9; // Shoes
    
    if(slot == 6) return -10; // Accessory
    
    if(slot == 7) return -1; // Primary
    if(slot == 8) return -2; // Secondary
    if(slot == 9) return -3; // Tertiary
    
    else return -11; // Null exception
}

FString AIngameHUD::ConvertClothingIndexToName(int slot) {
    if (slot == 0) return "Hat";
    if (slot == 1) return "Shirt";
    if (slot == 2) return "Vest";
    if (slot == 3) return "Bag";
    if (slot == 4) return "Pants";
    if (slot == 5) return "Shoes";
    
    if (slot == 6) return "Accessory";
    
    if (slot == 7) return "Primary Slot";
    if (slot == 8) return "Secondary Slot";
    if (slot == 9) return "Tertiary Slot";
    
    return "";
}

void AIngameHUD::DrawSelectedItem() {
    
    // Get player (And store to variable for easy access)
    APlayerCharacter* player = Cast<APlayerCharacter>(GetOwningPawn());
    if (!player) return; // Stop bad things from happening when (for whatever reason) the pointer to the player is NULL
    
    // Get inventory
    UInventoryComponent* inv = Cast<UInventoryComponent>(player->GetComponentsByClass(UInventoryComponent::StaticClass())[0]);
    
    FLinearColor dColour = FLinearColor(1, 1, 1); // White
    Canvas->DrawColor = dColour; // Set the colour
    
    int xPos = ClothingInventoryPosX < InventoryPosX ? ClothingInventoryPosX : InventoryPosX; // Get the position of the container - check which inventory is open more, and use that to prevent overlaping
    Canvas->DrawScaledIcon(ItemContainer, xPos - 115, 5 , FVector(0.4f, 0.4f, 0.4f)); // Draw the container
    
    // Draw item & name label
    AItem* item = inv->GetFromIndex(player->SelectedItem); // Get item
    if (item) {
        // Item icon
        if(item->Icon) Canvas->DrawScaledIcon(Canvas->MakeIcon(item->Icon), xPos - 115, 5 , FVector(0.4f, 0.4f, 0.4f)); // Draw the icon
        
        // Name Label
        FString name = item->Name; // Get the name
        
        // Calculate label size
        float nameX, nameY; // Variables
        Canvas->StrLen(AudiowideSmall, name, nameX, nameY); // function that calculates size
        
        FCanvasTextItem nameLabel = FCanvasTextItem(FVector2D(xPos - 120 - nameX, 45 - nameY / 2), FText::FromString(name), AudiowideSmall, FLinearColor(1, 1, 1)); // Canvas item for name
        nameLabel.ShadowColor = FColor::Black; // Add a shadow (Black)
        nameLabel.ShadowOffset = FVector2D(1, 1);
        
        Canvas->DrawItem(nameLabel);
    }
}
