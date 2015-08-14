// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NormalCharacter.h"
#include "AssassinCharacter.generated.h"

UENUM( BlueprintType )	//"BlueprintType" is essential to include
enum class EHuntSkillEnum : uint8
{
    HSE_ConcealedItem 	UMETA( DisplayName = "ConcealedItem" ),
    HSE_TargetItem 	UMETA( DisplayName = "TargetItem" ),
    HSE_Unique	UMETA( DisplayName = "Unique" )
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
    SE_Crawling UMETA( DisplayName = "Crawling" ),
    SE_Dead UMETA( DisplayName = "Dead" )
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

    virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const;

    void SetStabBegin();

    void SetStabOver();

private:
    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsStab;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = ( AllowPrivateAccess = "true" ) )
    EStatusEnum CurrentStatus;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = HuntSkill, meta = ( AllowPrivateAccess = "true" ) )
    EHuntSkillEnum CurrentHuntSkill;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = RunningSkill, meta = ( AllowPrivateAccess = "true" ) )
    ERunningSkillEnum CurrentRunningSkill;

    class AActor* ConcealedItemActor;

    FTimerHandle StabTimer;

    void UseSkill();

    virtual void UseConcealedItem();

    virtual void UseTargetItem();

    virtual void UseUnique();

    virtual void InitDagger();

    void SwitchConcealedItem();

    void SwitchTargetItem();

    void SwitchUnique();

    void SetStab( bool IsStab );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetStab( bool IsStab );
    virtual void ServerSetStab_Implementation( bool IsStab );
    virtual bool ServerSetStab_Validate( bool IsStab );

    void SetCurrentStatus( EStatusEnum Status );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetCurrentStatus( EStatusEnum Status );
    virtual void ServerSetCurrentStatus_Implementation( EStatusEnum Status );
    virtual bool ServerSetCurrentStatus_Validate( EStatusEnum Status );

    void SetCurrentHuntSkill( EHuntSkillEnum Skill );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetCurrentHuntSkill( EHuntSkillEnum Skill );
    virtual void ServerSetCurrentHuntSkill_Implementation( EHuntSkillEnum Skill );
    virtual bool ServerSetCurrentHuntSkill_Validate( EHuntSkillEnum Skill );

    void SetCurrentRunningSkill( ERunningSkillEnum Skill );

    UFUNCTION( reliable, server, WithValidation )
    void ServerSetCurrentRunningSkill( ERunningSkillEnum Skill );
    virtual void ServerSetCurrentRunningSkill_Implementation( ERunningSkillEnum Skill );
    virtual bool ServerSetCurrentRunningSkill_Validate( ERunningSkillEnum Skill );
};
