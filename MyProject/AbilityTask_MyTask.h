// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_MyTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMyTwoParamDelegate, float, FirstParamName, int32, SecondParamName);

/**
 * 
 */
UCLASS()
class MYPROJECT_API UAbilityTask_MyTask : public UAbilityTask
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintAssignable)
	FMyTwoParamDelegate OnCalled;

	void PerformAction() const;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ExecuteMyTask", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_MyTask* CreateMyTask(UGameplayAbility* OwningAbility, FName TaskInstanceName, float examplevariable);

	void Activate() override;
};
