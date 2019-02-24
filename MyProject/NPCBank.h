// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "NPCBank.generated.h"

/**
*
*/
USTRUCT(blueprintType)
struct FTableRowBank : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FTableRowBank()
		: PlayerMoney(0.0f)
	{
	}

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = ItemInfo)
	TArray<FTableRowInventory> BankMap;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = ItemInfo)
	float PlayerMoney;
};

/**
 * 
 */
UCLASS()
class MYPROJECT_API ANPCBank : public ANPC
{
	GENERATED_BODY()

public:
	ANPCBank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	void OpeningAnAccount(const FString &PlayerName, float price);

	UFUNCTION(BlueprintCallable, Category = "Sun")
	bool OpensTheAccountOf(const FString &PlayerName);

	UFUNCTION(BlueprintCallable, Category = "Sun")
	void RefreshAccount();

	UFUNCTION(BlueprintCallable, Category = "Sun")
	void CloseAccount();

	UFUNCTION(BlueprintCallable, Category = "Sun")
	void GiveObjectToPlayer(int32 IDItem);

private:
	FString PlayerContact;
	FTableRowBank* TableInventoryBank;
};
