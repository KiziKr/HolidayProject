// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "BagPlayer.h"
#include "PlayerEquipment.h"
#include "Engine.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	CarryingBag = nullptr;

	PlayerName = "KiziLom";

	MaxHealth = 100;
	CurrentHealth = MaxHealth;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

												   //Create a DropPoint
	DropPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Drop Object"));
	DropPoint->SetupAttachment(RootComponent);

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("OpenBag", IE_Released, this, &APlayerCharacter::OpenBag);

	//PlayerInputComponent->BindAction("InteractInventory", IE_Pressed, this, &ACharacter::OpenInventory);
	//PlayerInputComponent->BindAction("InteractInventory", IE_Released, this, &ACharacter::CloseInventory);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCharacter::TouchStopped);

	AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbiliyInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystem)
	{
		if (HasAuthority() && Ability)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, 0));
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

void APlayerCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->RefreshAbilityActorInfo();
}

void APlayerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void APlayerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}


void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::OpenBag()
{
	if (CarryingBag)
	{
		CarryingBag->SequenceBag();
	}
}

bool APlayerCharacter::EquipBag(ABagPlayer* TheBag)
{
	if(CarryingBag == nullptr /*&& TheBag->Item.Level <= Level*/)
	{
		CarryingBag = TheBag;
		TheBag->AttachToPlayer(this->GetMesh(), FName("BackpackSocket"));
		return true;
	}
	return false;
}

void APlayerCharacter::EquipItem(APlayerEquipment* TheItem)
{
	if (ABagPlayer* BagPlayer = Cast<ABagPlayer>(TheItem))
	{
		EquipBag(BagPlayer);
		return;
	}


	/*const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ItemCategory"), true);

	FString theKey = EnumPtr->GetNameStringByValue(theEquipment->Item.category.GetValue());



	if (mEquipment.Contains(theKey) && mEquipment[theKey] == NULL)
	{
		mEquipment.Add(theKey, theEquipment);
		FString test = theKey + "Socket";
		mEquipment[theKey]->AttachToPlayer(this->GetMesh(), FName(*test));
	}*/
}

void APlayerCharacter::DepositBag()
{
	if (GetVelocity().Size() == 0.0f)
	{
		//mCarryingBag->DetachFromPlayer(DropPoint->GetComponentLocation());
		//mCarryingBag = nullptr;
	}
}