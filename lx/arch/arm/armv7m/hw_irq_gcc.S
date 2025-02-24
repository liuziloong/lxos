@*******************************************************************************
@                              EXPORT FUNCTIONS
@*******************************************************************************

.global hw_local_irq_disable
.global hw_local_irq_enable
.global hw_local_irq_save
.global hw_local_irq_restore

@*******************************************************************************
@                              CODE GENERATION DIRECTIVES
@*******************************************************************************

.text
.align 2
.thumb
.syntax unified

@*******************************************************************************
@ Functions:
@     void hw_local_irq_disable(void);
@     void hw_local_irq_enable(void);
@*******************************************************************************
.thumb_func
hw_local_irq_disable:
    CPSID I
    BX    LR

.thumb_func
hw_local_irq_enable:
    CPSIE I
    BX    LR

@*******************************************************************************
@ Functions:
@     unsigned long hw_local_irq_save(void);
@     void hw_local_irq_restore(unsigned long flags);
@*******************************************************************************
.thumb_func
hw_local_irq_save:
    MRS   R0, PRIMASK
    CPSID I
    BX    LR

.thumb_func
hw_local_irq_restore:
    MSR   PRIMASK, R0
    BX    LR

