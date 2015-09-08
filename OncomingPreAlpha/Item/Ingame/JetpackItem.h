// All rights reserved Trifuse. Written by AidoP

#pragma once

#include "Item/Clothing/BagItem.h"
#include "JetpackItem.generated.h"

/**
 * 
 */
UCLASS()
class ONCOMINGPREALPHA_API AJetpackItem : public ABagItem
{
	GENERATED_UCLASS_BODY()
	
	
	
    virtual void QuaternaryClothingPress(APlayerCharacter* player) override;
    virtual void QuaternaryClothingRelease(APlayerCharacter* player) override;
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
};
