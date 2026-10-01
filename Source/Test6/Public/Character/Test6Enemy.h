

#pragma once

#include "CoreMinimal.h"
#include "Character/Test6Character.h"
#include "Test6Enemy.generated.h"

class UEnemyAttributeSet;

/**
 * 
 */
UCLASS()
class TEST6_API ATest6Enemy : public ATest6Character
{
	GENERATED_BODY()

public:
	ATest6Enemy();
	UEnemyAttributeSet* GetStatAttribute() const;

protected:
	virtual void PossessedBy(AController* NewController) override;

protected:

	// 적 전용 어트리뷰트 셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UEnemyAttributeSet> EnemyAttributeSet;
};
