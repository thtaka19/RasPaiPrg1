/*
 * This file was automatically generated by tecsgen.
 * This file is not intended to be edited.
 */
#ifndef siSemaphore_TECSGEN_H
#define siSemaphore_TECSGEN_H

/*
 * signature   :  siSemaphore
 * global name :  siSemaphore
 * context     :  non-task
 */

#ifndef TOPPERS_MACRO_ONLY

/* signature descriptor #_SD_# */
struct tag_siSemaphore_VDES {
    struct tag_siSemaphore_VMT *VMT;
};

/* signature function table #_SFT_# */
struct tag_siSemaphore_VMT {
    ER             (*signal__T)( const struct tag_siSemaphore_VDES *edp );
};

/* signature descriptor #_SDES_# for dynamic join */
typedef struct { struct tag_siSemaphore_VDES *vdes; } Descriptor( siSemaphore );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SISEMAPHORE_SIGNAL              (1)

#endif /* siSemaphore_TECSGEN_H */
