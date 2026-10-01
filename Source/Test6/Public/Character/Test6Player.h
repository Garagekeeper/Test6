

#pragma once

#include "CoreMinimal.h"
#include "Character/Test6Character.h"
#include "Test6Player.generated.h"

class UPlayerAttributeSet;

/**
 * 
 */
UCLASS()
class TEST6_API ATest6Player : public ATest6Character
{
	GENERATED_BODY()

public:
	ATest6Player();
	UPlayerAttributeSet* GetStatAttribute() const;

protected:
	virtual void PossessedBy(AController* NewController) override;
	

protected:

	// 플레이어 전용 어트리뷰트셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet;
};
