// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArcCharacter.h"
#include "Engine/World.h"
#include "Materials/Material.h"
#include "LostArcPlayerController.h"
#include "LostArcCharacterAnimInstance.h"
#include "LostArcPlayerCombatComponent.h"
#include "LostArcCharacterStatComponent.h"
#include "HUDWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ALostArcCharacter::ALostArcCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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

	// Create an autoAttack instance that is responsible for the default attack of the character. 
	CombatComponent = CreateDefaultSubobject<ULostArcPlayerCombatComponent>(TEXT("COMBAT"));
	StatComponent = CreateDefaultSubobject<ULostArcCharacterStatComponent>(TEXT("STAT"));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ALostArcCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ArcanimInstance = Cast<ULostArcCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (ArcanimInstance == nullptr) return;
	
	ArcanimInstance->OnNextAttackCheck.AddLambda([this]()->void {CombatComponent->BasicAttackNextComboCheck(); });
	ArcanimInstance->OnSkillHitCheck.AddLambda([this](int32 val)->void {CombatComponent->SkillHitCheck(val); });
	ArcanimInstance->OnMontageEnded.AddDynamic(this, &ALostArcCharacter::CallOnAttackMontageEnded); // ※ AddDynamic 매크로의 바인딩은 해당 클래스 내의 멤버 함수를 대상으로 해야한다. (자주 끊어져서)
	
	StatComponent->OnHPIsZero.AddLambda([this]()->void {ArcanimInstance->SetDeadAnim(); SetActorEnableCollision(false); Cast<ALostArcPlayerController>(GetController())->SetInputMode(FInputModeUIOnly()); });
}

void ALostArcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Evade", IE_Pressed, this, &ALostArcCharacter::Evade);

	InputComponent->BindAction<FBindActionDelegate>("BasicAttack", IE_Pressed, this, &ALostArcCharacter::CalltoSkillCast, 0);
	InputComponent->BindAction<FBindActionDelegate>("Skill_A", IE_Pressed, this, &ALostArcCharacter::CalltoSkillCast, 1);
	InputComponent->BindAction<FBindActionDelegate>("Skill_B", IE_Pressed, this, &ALostArcCharacter::CalltoSkillCast, 2);
	InputComponent->BindAction<FBindActionDelegate>("Skill_C", IE_Pressed, this, &ALostArcCharacter::CalltoSkillCast, 3);
	InputComponent->BindAction<FBindActionDelegate>("Skill_D", IE_Pressed, this, &ALostArcCharacter::CalltoSkillCast, 4);
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

void ALostArcCharacter::CharacterRotatetoCursor()
{
	FHitResult Hit;
	Cast<ALostArcPlayerController>(GetController())->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	float ang = FMath::Atan2(Hit.ImpactPoint.Y - GetActorLocation().Y, Hit.ImpactPoint.X - GetActorLocation().X) * 180 / PI;
	if (ang < 0) ang += 360;
	SetActorRelativeRotation(FRotator(0.0f, ang, 0.0f));
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), this);
}

void ALostArcCharacter::Evade()
{
	auto Anim = Cast<ULostArcCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (Anim == nullptr || bEvading) return;

	CharacterRotatetoCursor();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacterEvade"));

	bEvading = true;
	Anim->Montage_Play(Anim->EvadeMontage, 1.f); // Montage_Play()가 시작되면 이전에 실행 중이던 몽타주는 자동으로 End된다. 
}

void ALostArcCharacter::CalltoSkillCast(int32 Slot)
{
	if (bEvading) return;

	if (Slot) // Skill Cast
	{
		if (CombatComponent->bSkillCasting) return;
		CharacterRotatetoCursor();
		CombatComponent->SkillCast(Slot);
	}
	else // Basic Attack
	{
		if (CombatComponent->bSkillCasting && !CombatComponent->bBasicAttacking) return;
		CombatComponent->SkillCast(Slot);
	}
}

void ALostArcCharacter::CallOnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CombatComponent->bSkillCasting = false;

	if (Montage->IsValidSectionName(TEXT("Attack1")))
	{
		CombatComponent->bBasicAttacking = false;
		CombatComponent->BasicAttackEndComboState();
	}
	if (Montage->IsValidSectionName(TEXT("Skill_A")))
	{
		if (bInterrupted)
			UE_LOG(LogTemp, Warning, TEXT("Evade!"));
			
		//UE_LOG(LogTemp, Warning,TEXT("%f"), StatComponent->getHP());
	}
	if (Montage->IsValidSectionName(TEXT("Evade")))
	{
		bEvading = false;
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("ArcCharacter"));
	}
}

float ALostArcCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	StatComponent->SetDamage(FinalDamage);
	return FinalDamage;
}





