// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/DataTable.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"


/**
*
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, Category = ItemInfo)
	TArray<FTableRowInventory> InventoryComponentItems;

	//UPROPERTY()
	//TMap<FString, FConversations> InventoryMap;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void SetInventoryTable(UDataTable* DataTable)
	{ 
		InventoryTable = DataTable;
	}

	UDataTable* GetInventoryTable() { return InventoryTable; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template<typename T>
	T* GetItemsRow(const FName &RowName)
	{
		if (!GetInventoryTable())
		{
			//UELOG(Debug message plutot sympa)
			return nullptr;
		}

		return GetInventoryTable()->FindRow<T>(RowName, FString());
	}

	template<typename T>
	TArray<T*> GetItemsByCategory(const TArray<TEnumAsByte<ItemCategory>> &CategorySell)
	{//Refracto -> ForeachRow()
		TArray<T*> ItemsResult;

		if (InventoryTable)
		{
			TArray<T*> ItemsTable;
			InventoryTable->GetAllRows<FTableRowInventory>(FString(), ItemsTable);

			for (T* ItemInfoRow : ItemsTable)
			{
				if (CategorySell.Contains(ItemInfoRow->ItemData.category.GetValue()))
				{
					ItemsResult.Add(ItemInfoRow);
				}
			}
		}

		return ItemsResult;
	}

	void RemoveItem(const FItemData &item);

	TArray<FTableRowInventory*> GetItemsByCategory(const TArray<TEnumAsByte<ItemCategory>> &CategorySell);

private:

	void SortItemByName(const FTableRowInventory *item);

	void SortItemByStats(const FTableRowInventory *item);

private:
	UPROPERTY(VisibleAnyWhere, Category=InventoryComponent)
	UDataTable* InventoryTable;
};