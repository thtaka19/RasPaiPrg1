/*
 * This file was automatically generated by tecsgen.
 * This file is not intended to be edited.
 */
#ifndef sTaskBody_TECSGEN_H
#define sTaskBody_TECSGEN_H

/*
 * signature   :  sTaskBody
 * global name :  sTaskBody
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* signature descriptor #_SD_# */
struct tag_sTaskBody_VDES {
    struct tag_sTaskBody_VMT *VMT;
};

/* signature function table #_SFT_# */
struct tag_sTaskBody_VMT {
    void           (*main__T)( const struct tag_sTaskBody_VDES *edp );
};

/* signature descriptor #_SDES_# for dynamic join */
typedef struct { struct tag_sTaskBody_VDES *vdes; } Descriptor( sTaskBody );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_STASKBODY_MAIN                  (1)

#endif /* sTaskBody_TECSGEN_H */
