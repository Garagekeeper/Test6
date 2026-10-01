

#pragma once

#include "CoreMinimal.h"
#include "Character/Test6Character.h"
#include "GameplayAbilitySpecHandle.h"
#include "Test6Player.generated.h"

class UPlayerAttributeSet;
class UGameplayAbility;
class UInputAction;
class UEnhancedInputComponent;

/**
 * 어빌리티 입력 식별용 열거형 (GAS InputID로 변환되어 바인딩됨)
 */
UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	Fireball	UMETA(DisplayName = "Fireball")
};

/**
 * 어빌리티 개별 등록 설정 구조체
 */
USTRUCT(BlueprintType)
struct FPlayerAbilityConfig
{
	GENERATED_BODY()

	/** 부여할 어빌리티 클래스 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> AbilityClass = nullptr;

	/** 어빌리티 기본 레벨 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (ClampMin = "1"))
	int32 AbilityLevel = 1;

	/** 바인딩할 어빌리티 입력 식별자 (입력이 필요 없는 패시브의 경우 None) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	EAbilityInputID InputID = EAbilityInputID::None;

	/** 트리거용 향상된 입력 액션 (IA). 패시브이거나 직접 호출 어빌리티인 경우 비워둘 수 있음 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputAction = nullptr;

	/** 어빌리티 부여 즉시 자동 활성화 여부 (패시브 등) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	bool bActivateOnGranted = false;
};

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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GiveDefaultAbilites();
	// 어빌리티에 인풋액션 바인딩
	virtual void SetupAbilityInputs(UEnhancedInputComponent* EnhancedInputComponent);

	// 키가 눌렸을때 해당 키에 등록된 채널로 입력을 전피
	// 해당 채널의 어빌리티가 있으면 해당 어빌리티 작동 시도
	void OnAbilityInputPressed(EAbilityInputID InputID);
	void OnAbilityInputReleased(EAbilityInputID InputID);

protected:

	// 플레이어 전용 어트리뷰트셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet;

	// 기본 어빌리티
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<FPlayerAbilityConfig> DefaultAbilities;

private:
	/** 부여된 디폴트 어빌리티들의 핸들 목록 */
	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> GrantedDefaultAbilityHandles;
};
