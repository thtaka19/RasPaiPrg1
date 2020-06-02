/*
 * This file was automatically generated by tecsgen.
 * This file is not intended to be edited.
 */
#ifndef sSerialPort_TECSGEN_H
#define sSerialPort_TECSGEN_H

/*
 * signature   :  sSerialPort
 * global name :  sSerialPort
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* signature descriptor #_SD_# */
struct tag_sSerialPort_VDES {
    struct tag_sSerialPort_VMT *VMT;
};

/* signature function table #_SFT_# */
struct tag_sSerialPort_VMT {
    ER             (*open__T)( const struct tag_sSerialPort_VDES *edp );
    ER             (*close__T)( const struct tag_sSerialPort_VDES *edp );
    ER_UINT        (*read__T)( const struct tag_sSerialPort_VDES *edp, char* buffer, uint_t length );
    ER_UINT        (*write__T)( const struct tag_sSerialPort_VDES *edp, const char* buffer, uint_t length );
    ER             (*control__T)( const struct tag_sSerialPort_VDES *edp, uint_t ioControl );
    ER             (*refer__T)( const struct tag_sSerialPort_VDES *edp, T_SERIAL_RPOR* pk_rpor );
};

/* signature descriptor #_SDES_# for dynamic join */
typedef struct { struct tag_sSerialPort_VDES *vdes; } Descriptor( sSerialPort );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SSERIALPORT_OPEN                (1)
#define	FUNCID_SSERIALPORT_CLOSE               (2)
#define	FUNCID_SSERIALPORT_READ                (3)
#define	FUNCID_SSERIALPORT_WRITE               (4)
#define	FUNCID_SSERIALPORT_CONTROL             (5)
#define	FUNCID_SSERIALPORT_REFER               (6)

#endif /* sSerialPort_TECSGEN_H */
