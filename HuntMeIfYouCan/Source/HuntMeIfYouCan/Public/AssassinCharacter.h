// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NormalCharacter.h"
#include "AssassinCharacter.generated.h"

UENUM( BlueprintType )	//"BlueprintType" is essential to include
enum class EHuntSkillEnum : uint8
{
    HSE_ConcealedItem 	UMETA( DisplayName = "ConcealedItem" ),
    HSE_TargetItem 	UMETA( DisplayName = "TargetItem" ),
    HSE_Specific	UMETA( DisplayName = "Specific" )
};

UENUM( BlueprintType )
enum class ERunningSkillEnum : uint8
{
    RSE_DriftItem 	UMETA( DisplayName = "DriftItem" ),
    RSE_Dodge UMETA( DisplayName = "Dodge" )
};

UENUM( BlueprintType )
enum class EStatusEnum : uint8
{
    SE_Masquerade 	UMETA( DisplayName = "Masquerade" ),
    SE_Expose UMETA( DisplayName = "Expose" ),
    SE_Crawling UMETA( DisplayName = "Crawling" )
};

UCLASS()
class HUNTMEIFYOUCAN_API AAssassinCharacter : public ANormalCharacter
{
    GENERATED_BODY()
public:
    // Sets default values for this character's properties
    AAssassinCharacter();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaTime ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;

    void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const;

    UFUNCTION( BlueprintCallable, Category = Action )
    void SetStab( bool IsStab );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetStab( bool IsStab );
    virtual void ServerSetStab_Implementation( bool IsStab );
    virtual bool ServerSetStab_Validate( bool IsStab );

    UFUNCTION( BlueprintCallable, category = SkillSwitch )
    void SetCurrentHuntSkill( EHuntSkillEnum Skill );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetCurrentHuntSkill( EHuntSkillEnum Skill );
    virtual void ServerSetCurrentHuntSkill_Implementation( EHuntSkillEnum Skill );
    virtual bool ServerSetCurrentHuntSkill_Validate( EHuntSkillEnum Skill );

private:
    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsStab;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = ( AllowPrivateAccess = "true" ) )
    EStatusEnum CurrentStatus;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = HuntSkill, meta = ( AllowPrivateAccess = "true" ) )
    EHuntSkillEnum CurrentHuntSkill;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = RunningSkill, meta = ( AllowPrivateAccess = "true" ) )
    ERunningSkillEnum CurrentRunningSkill;

    void UseSkill();

    void SwitchConcealedItem();

    void SwitchTargetItem();
};
