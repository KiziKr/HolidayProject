// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEquipment.h"
#include "InventoryUserWidget.h"
#include "BagPlayer.generated.h"

UCLASS()
class MYPROJECT_API ABagPlayer : public APlayerEquipment
{
	GENERATED_BODY()

	UPROPERTY()
	UInventoryUserWidget* InventoryUserWidget_0;

	UPROPERTY()
	UInventoryUserWidget* InventoryUserWidget_1;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInventoryUserWidget> wInventoryUserWidget_0;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TSubclassOf<UInventoryUserWidget> wInventoryUserWidget_1;

public:
	// Sets default values for this actor's properties
	ABagPlayer();

private:
	int32 NumberItemCategory(TEnumAsByte<ItemCategory> category);

	FString ConvertCategoryString(TEnumAsByte<ItemCategory> category);

	FTableRowInventory* HasBrother(const FTableRowInventory &Item);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UFUNCTION()
	void OnGameObject(AActor* Target, FKey ButtonPressed) override;*/

	virtual void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool AddItem(const FTableRowInventory &Item, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category=BagPlayer)
	void OpenBag();

	UFUNCTION(BlueprintCallable, Category = BagPlayer)
	void CloseBag();

	void InspectBag();

	UFUNCTION(BlueprintCallable, Category=testWidget)
	UInventoryUserWidget* GetWidgetBag()
	{
		return InventoryUserWidget_0;
	}

	UFUNCTION(BlueprintCallable, Category = testWidget)
	bool IsOpen() { return bIsOpen; }

	void RefreshBag();

	UFUNCTION(BlueprintCallable, Category = testWidget)
	void SequenceBag();

	UFUNCTION(BlueprintCallable, Category=testWidget)
	int32 GetCurrentWeight()
	{
		return Weight;
	}

	void SetCurrentWeight(int32 NewCurrentWeight) { Weight = NewCurrentWeight;  }

private:
	UPROPERTY(EditAnyWhere, Category = ItemInfo)
	TArray<FTableRowInventory> InventoryBagPlayer;

	int32 Weight;

	UPROPERTY(EditAnyWhere, Category = InventoryComponent)
	int32 MaxWeight;

	UPROPERTY(EditAnyWhere, Category = InventoryComponent)
	int32 MaxLimit;

	bool bIsOpen;
};