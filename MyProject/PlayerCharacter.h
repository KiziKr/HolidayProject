// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BagPlayer.h"
#include "ItemData.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class APlayerEquipment;

UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	UseAbility1 UMETA(DisplayName = "Use Spell 1"),
	UseAbility2 UMETA(DisplayName = "Use Spell 2"),
	UseAbility3 UMETA(DisplayName = "Use Spell 3"),
	UseAbility4 UMETA(DisplayName = "Use Spell 4"),
	WeaponAbility UMETA(DisplayName = "Use Weapon"), 
};

/**
*/

UCLASS(config = Game)
class APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* DropPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	void DepositBag();

	UPROPERTY(VisibleAnyWhere, Category=Inventory)
	ABagPlayer* CarryingBag;

public:
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TSubclassOf<class UGameplayAbility> Ability;

	virtual void PossessedBy(AController* NewController) override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerEquipment")
	TMap<FString, APlayerEquipment*> mEquipment;

	void EquipItem(APlayerEquipment* TheItem);

	bool EquipBag(ABagPlayer* TheBag);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	/** */
	FString PlayerName;

	UPROPERTY(EditAnyWhere, Category = ItemInfo)
	TArray<FTableRowInventory> InventoryPlayer;

	/** */
	int32 CurrentHealth;

	/** */
	int32 MaxHealth;

	void OpenBag();
	
public:
	UFUNCTION(BlueprintCallable, Category = BagPlayer)
	FString GetPlayerName() { return PlayerName; }

	UFUNCTION(BlueprintCallable, Category=BagPlayer)
	ABagPlayer* GetCarryingBag() { return CarryingBag; }
};

