// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntMeIfYouCan.h"
#include "NormalCharacter.h"


// Sets default values
ANormalCharacter::ANormalCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationYaw = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    Camera->AttachTo(RootComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    Camera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
    Camera->RelativeLocation = FVector(20.0f, 0.0f, 10.0f);

    GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void ANormalCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ANormalCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ANormalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void ANormalCharacter::MoveForward(float Value)
{
    // find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get forward vector
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, Value);
}

void ANormalCharacter::MoveRight(float Value)
{
    // find out which way is right
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get right vector
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    // add movement in that direction
    AddMovementInput(Direction, Value);
}


