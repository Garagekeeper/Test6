


#include "Character/Test6Enemy.h"
#include "GAS/EnemyAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/OverHeadWidget.h"

ATest6Enemy::ATest6Enemy()
{
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("Stat"));

	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidgetComp"));
	OverHeadWidgetComponent->SetupAttachment(RootComponent);

	OverHeadWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	OverHeadWidgetComponent->SetDrawSize(FVector2D(150.0f, 20.0f));
	OverHeadWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	OverHeadWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UEnemyAttributeSet* ATest6Enemy::GetStatAttribute() const
{
	return EnemyAttributeSet;
}

void ATest6Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeOverHeadWidget();
}

void ATest6Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateOverheadWidgetRotation();
}

void ATest6Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	// 타이밍 문제로 한번 더 처리해서 확인
	InitializeOverHeadWidget();
}

void ATest6Enemy::InitializeOverHeadWidget()
{
	if (!OverHeadWidgetComponent) return;

	if (UUserWidget* UserWidget = OverHeadWidgetComponent->GetUserWidgetObject())
	{
		if (UOverHeadWidget* OverHeadWidget = Cast<UOverHeadWidget>(UserWidget))
		{
			OverHeadWidget->InitWidget(this);
		}
	}
}

void ATest6Enemy::UpdateOverheadWidgetRotation()
{
	if (!OverHeadWidgetComponent) return;

	if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		// 카메라의 전방 벡터와 정확히 마주보는 방향(-CameraForward, 사이각 180도)으로 회전
		const FVector CameraForward = CameraManager->GetCameraRotation().Vector();
		FRotator WidgetRotation = (-CameraForward).Rotation();
		//yaw회전만 사용
		WidgetRotation.Pitch = 0.0f;
		WidgetRotation.Roll = 0.0f;

		OverHeadWidgetComponent->SetWorldRotation(WidgetRotation);
	}
}
