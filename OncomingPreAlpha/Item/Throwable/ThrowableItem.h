#pragma once

#include "Item/Item.h"
#include "ThrowableItem.generated.h"

/**
 * 
 */
UCLASS()
class ONCOMINGPREALPHA_API AThrowableItem : public AItem
{
	GENERATED_UCLASS_BODY()
	
	
    float Mass; // Important for projectile calculations
    FVector ThrowVelocity; // Important for projectile calculations - Starting velocity to throw item at
    
    void Throw(APlayerCharacter* player);
    
    virtual void TertiaryPress(APlayerCharacter* player) override;
	
};
