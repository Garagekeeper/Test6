

#pragma once

#include "CoreMinimal.h"
#include "Character/Test6Character.h"
#include "Test6Enemy.generated.h"

class UEnemyAttributeSet;
class UWidgetComponent;

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
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitializeOverHeadWidget();

	// 위젯의 빌보드 기능 구현
	virtual void UpdateOverheadWidgetRotation();

protected:

	// 적 전용 어트리뷰트 셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UEnemyAttributeSet> EnemyAttributeSet;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OverHead")
	TObjectPtr<UWidgetComponent> OverHeadWidgetComponent;
};
