// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/LostArcCharacter.h"
#include "Engine/World.h"
#include "Materials/Material.h"
#include "Controller/LostArcPlayerController.h"
#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Player/LostArcCharacterAbilityComponent.h"
#include "Player/LostArcInventoryComponent.h"
#include "LineOfSightComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Abilities/LostArcSkill_BasicAttack.h"

ALostArcCharacter::ALostArcCharacter()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 900.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Attach the mannequin skeletal mesh...
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANNEQUIN(TEXT("SkeletalMesh'/Game/ArcCharacter/Player/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SK_MANNEQUIN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MANNEQUIN.Object);
	}

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/ArcCharacter/Player/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Create main Weapon and mount it in a socket
	FName WeaponSocket(TEXT("hand_rWeapon"));
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/Weapon_Pack/Skeletal_Mesh/SK_Sword.SK_Sword"));
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		}
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}

	StatComponent = CreateDefaultSubobject<ULostArcCharacterStatComponent>(TEXT("STAT"));
	AbilityComponent = CreateDefaultSubobject<ULostArcCharacterAbilityComponent>(TEXT("ABILITY"));
	InventoryCompoennt = CreateDefaultSubobject<ULostArcInventoryComponent>(TEXT("INVENTORY"));
}

void ALostArcCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AnimInstance = Cast<ULostArcCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (AnimInstance != nullptr)
	{
		AnimInstance->OnNextBasicAttackCheck.AddLambda([this]()->void { Cast<ULostArcSkill_BasicAttack>(AbilityComponent->GetAbilites(EAbilityType::BasicAttack))->BasicAttackNextComboCheck(this); });
		AnimInstance->OnMeleeSkillHitCheck.AddLambda([this](EAbilityType Type)->void { AbilityComponent->AbilityHitDetection(Type); });
		AnimInstance->OnMontageEnded.AddDynamic(AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityMontageEnded); // ※ AddDynamic 매크로의 바인딩은 해당 클래스 내의 멤버 함수를 대상으로 해야한다. (자주 끊어져서)
	}
	StatComponent->OnHPIsZero.AddLambda([this]()->void {AnimInstance->SetDeadAnim(); SetActorEnableCollision(false); Cast<ALostArcPlayerController>(GetController())->SetInputMode(FInputModeUIOnly()); });
}

void ALostArcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction<FBindAbilityDelegate>("BasicAttack", IE_Pressed, AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityCast, EAbilityType::BasicAttack);
	InputComponent->BindAction<FBindAbilityDelegate>("MeleeSkill_1", IE_Pressed, AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityCast, EAbilityType::MeleeSkill_1);
	InputComponent->BindAction<FBindAbilityDelegate>("MeleeSkill_2", IE_Pressed, AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityCast, EAbilityType::MeleeSkill_2);
	InputComponent->BindAction<FBindAbilityDelegate>("MeleeSkill_3", IE_Pressed, AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityCast, EAbilityType::MeleeSkill_3);
	InputComponent->BindAction<FBindAbilityDelegate>("MeleeSkill_4", IE_Pressed, AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityCast, EAbilityType::MeleeSkill_4);
	InputComponent->BindAction<FBindAbilityDelegate>("Evade", IE_Pressed, AbilityComponent, &ULostArcCharacterAbilityComponent::AbilityCast, EAbilityType::Evade);
}

void ALostArcCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALostArcCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	/* CursorToWorld is an aura that tracks the mouse cursor. */
	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

float ALostArcCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	StatComponent->SetDamage(FinalDamage);
	return FinalDamage;
}