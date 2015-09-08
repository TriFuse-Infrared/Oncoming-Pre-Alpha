// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

DECLARE_LOG_CATEGORY_EXTERN(OncomingOutput, Log, All);


enum UserOptions {
    AnimateInventory,
    InventoryColour,
    InventorySelectColour
};

union OptionValue {
public:
    
    OptionValue(int Value) {
        intValue = Value;
    }
    
    OptionValue(float Value) {
        floatValue = Value;
    }
    
    OptionValue(bool Value) {
        boolValue = Value;
    }
    
    OptionValue(FString Value) {
        stringValue = Value;
    }
    
    
    
    int     intValue;
    float   floatValue;
    bool    boolValue;
    FString stringValue;
};


class SettingsRetrieval {
private:
    TMap<UserOptions, OptionValue> Settings;
    
    // Initialise user options!
    SettingsRetrieval() {
        // Load from file.
    }
    
public:
    
    
    bool AnimateInventory() {
        return Settings[UserOptions::AnimateInventory].boolValue;
    }
    
};