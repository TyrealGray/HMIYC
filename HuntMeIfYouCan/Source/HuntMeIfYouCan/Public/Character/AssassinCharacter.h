// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NormalCharacter.h"
#include "Projectile/ArrowProjectile.h"
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

    virtual void UseConcealedItem();

    virtual void UseConcealedItemConfirmed();

    virtual void UseTargetItem();

    virtual void UseUnique();

    virtual void UseTargetItemConfirmed();

    UFUNCTION( NetMulticast, Unreliable )
    void BeExpose();

    virtual void Exposed();

    void PlayExposedBGM();

    void BeCrawling();

    void BeDying();

    virtual void GoIntoStatus( EStatusEnum NewStatus );

    void GoCrawling();

    void GoMasquerade();

    virtual bool OnPlayerHit( class AAssassinCharacter *Assassin = nullptr ) override;

    UFUNCTION( NetMulticast, Reliable )
    void BeScoring( float Score );

    UTexture2D *GetMeshTexture( int32 ID );

    virtual FString GetUIPath();

private:

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsStab;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Action, meta = ( AllowPrivateAccess = "true" ) )
    bool bIsHoldBow;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = ( AllowPrivateAccess = "true" ) )
    EStatusEnum CurrentStatus;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = HuntSkill, meta = ( AllowPrivateAccess = "true" ) )
    EHuntSkillEnum CurrentHuntSkill;

    UPROPERTY( Replicated, VisibleAnywhere, BlueprintReadOnly, Category = RunningSkill, meta = ( AllowPrivateAccess = "true" ) )
    ERunningSkillEnum CurrentRunningSkill;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = BodyMaterial, meta = ( AllowPrivateAccess = "true" ) )
    UTexture2D * HeadMeshTexture;

    UPROPERTY(  EditDefaultsOnly, BlueprintReadWrite, Category = BodyMaterial, meta = ( AllowPrivateAccess = "true" ) )
    UTexture2D * HandMeshTexture;

    UPROPERTY(  EditDefaultsOnly, BlueprintReadWrite, Category = BodyMaterial, meta = ( AllowPrivateAccess = "true" ) )
    UTexture2D * FootMeshTexture;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = BodyMaterial, meta = ( AllowPrivateAccess = "true" ) )
    UTexture2D * BodyMeshTexture;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = ItemActor, meta = ( AllowPrivateAccess = "true" ) )
    TSubclassOf<AActor> DaggerActorClass;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = ItemActor, meta = ( AllowPrivateAccess = "true" ) )
    TSubclassOf<AActor> BowActorClass;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay, meta = ( AllowPrivateAccess = "true" ) )
    class USoundBase * FireConcealedItemSound;

    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay, meta = ( AllowPrivateAccess = "true" ) )
    class USoundBase * FireTargetItemSound;

    UPROPERTY( EditDefaultsOnly, Category = Projectile, meta = ( AllowPrivateAccess = "true" ) )
    TSubclassOf<class AArrowProjectile> ArrowProjectileClass;

    bool bIsTargetItemColdDown;

    FVector BowOffset;

    AActor *ConcealedItemActor;

    AActor* TargetItemActor;

    FTimerHandle StabTimer;

    FTimerHandle ExposeTimer;

    FTimerHandle CrawlingTimer;

    FTimerHandle DyingTimer;

    // still not sure : does timer need to be replicated?
    FTimerHandle TargetItemColdDownTimer;

    class USoundWave* ExposeBGM;

    class UAudioComponent* ExposeBGMAudio;

    void UseSkill();

    void UseSkillConfirmed();

    virtual void JumpPrepared();

    virtual void JumpDeliver();

    virtual void InitDagger();

    virtual void InitBow();

    void SwitchConcealedItem();

    void SwitchTargetItem();

    void SwitchUnique();

    void GoDead();

    void SetStab( bool IsStab );

    void TargetItemColdDown();

    void TargetItemReady();

    void ItemHide();

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerUseConcealedItem();
    virtual void ServerUseConcealedItem_Implementation();
    virtual bool ServerUseConcealedItem_Validate();

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerUseConcealedItemConfirmed();
    virtual void ServerUseConcealedItemConfirmed_Implementation();
    virtual bool ServerUseConcealedItemConfirmed_Validate();

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerUseTargetItem();
    virtual void ServerUseTargetItem_Implementation();
    virtual bool ServerUseTargetItem_Validate();

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerUseTargetItemConfirmed();
    virtual void ServerUseTargetItemConfirmed_Implementation();
    virtual bool ServerUseTargetItemConfirmed_Validate();

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerItemHide();
    virtual void ServerItemHide_Implementation();
    virtual bool ServerItemHide_Validate();

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerSetStab( bool IsStab );
    virtual void ServerSetStab_Implementation( bool IsStab );
    virtual bool ServerSetStab_Validate( bool IsStab );

    void SetIsHoldBow( bool IsHoldBow );

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerSetIsHoldBow( bool IsHoldBow );
    virtual void ServerSetIsHoldBow_Implementation( bool IsHoldBow );
    virtual bool ServerSetIsHoldBow_Validate( bool IsHoldBow );

    void SetCurrentStatus( EStatusEnum Status );

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerSetCurrentStatus( EStatusEnum Status );
    virtual void ServerSetCurrentStatus_Implementation( EStatusEnum Status );
    virtual bool ServerSetCurrentStatus_Validate( EStatusEnum Status );

    void SetCurrentHuntSkill( EHuntSkillEnum Skill );

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerSetCurrentHuntSkill( EHuntSkillEnum Skill );
    virtual void ServerSetCurrentHuntSkill_Implementation( EHuntSkillEnum Skill );
    virtual bool ServerSetCurrentHuntSkill_Validate( EHuntSkillEnum Skill );

    void SetCurrentRunningSkill( ERunningSkillEnum Skill );

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerSetCurrentRunningSkill( ERunningSkillEnum Skill );
    virtual void ServerSetCurrentRunningSkill_Implementation( ERunningSkillEnum Skill );
    virtual bool ServerSetCurrentRunningSkill_Validate( ERunningSkillEnum Skill );

    UFUNCTION( Server, Reliable, WithValidation )
    void ServerBeDying( AController* PlayerController );
    virtual void ServerBeDying_Implementation( AController* PlayerController );
    virtual bool ServerBeDying_Validate( AController* PlayerController );
};
