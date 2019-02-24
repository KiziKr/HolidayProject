#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "Engine/Texture2D.h"
#include "ItemData.generated.h"

UENUM()
enum ItemCategory
{
	Hat,
	Shoulder,
	Mantle,
	Backpack,
	Amulet,
	Ring,
	Belt,
	Boots,
	Bread,
	Potion,
	Resource
};

USTRUCT(blueprintType)
struct FItemStats
{
	GENERATED_USTRUCT_BODY()

	FItemStats()
	{
		Vitality = 0;
		Strenght = 0;
		Intelligence = 0;
		Agility = 0;
	}

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 Vitality;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 Strenght;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 Intelligence;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 Agility;
};


USTRUCT(blueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	FItemData()
		: id(-1)
		, Level(0)
		, name("Unknown")
		, sprite(nullptr)
		, Description("Any")
		, weight(0)
	{
	}

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 id;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 Level;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	FString name;

	UPROPERTY(EditAnyWhere , BlueprintReadOnly, Category = Item)
	UTexture2D* sprite;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	TEnumAsByte<ItemCategory> category;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	FItemStats ItemStats;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	FString Description;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Item)
	int32 weight;
};

/**
*
*/
USTRUCT(blueprintType)
struct FTableRowInventory : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FTableRowInventory()
		: StaticMesh(nullptr)
	{
	}

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Info")
	FItemData	ItemData;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Info")
	bool		bCanBeEquipped;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Info")
	class		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Info")
	int32		Quantity;
};

/*
USTRUCT(blueprintType)
struct FItemMetaData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FTableRowInventory()
		: StaticMesh(nullptr)
	{
	}

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	FItemData	ItemData;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	class		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	bool		bCanBeEquipped;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	bool		bCanStack;
};
*/
USTRUCT(blueprintType)
struct FConversations
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnyWhere, Category = Inventory)
	TArray<FTableRowInventory> Entries;
};


USTRUCT(blueprintType)
struct FArrayString
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnyWhere, Category = Inventory)
	TArray<FString> FoString;
};