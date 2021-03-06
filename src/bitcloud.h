#ifndef _BITCLOUD_H
#define _BITCLOUD_H

#include <libuv.h>
#include <nss.h>
#include <sqlite3.h>

#include <stdint.h>
#include <stdarg.h>
#include <time.h>

/* Error codes: */
typedef enum BCError {
  BC_OK=0,
  BC_DB_ERROR,
  BC_BAD_DATA,
  BC_BAD_SIGNATURE,
  BC_NOT_FOUND,
  BC_SERVER_ERROR,
  BC_NO_CONNECTION,
  BC_DROP_CONNECTION,
  BC_BAD_DNS,
  BC_BAD_ROUTE,
  BC_UNEXPECTED_END,
  BC_CORRUPT_DATA
} BCError;

typedef uint32_t BCKey[8]; /* 256bits for keys */
typedef int Bool;
typedef time_t BCTime;
typedef int32_t BCInteger;
typedef int64_t BCSize;


/*
  Nodepool database structures and functions
*/

int bc_open_nodepool (const char* filename);

/* general authorization callback function for stlite: */
BCError bc_auth (void *user_data,
                 int even_code,
                 const char *event_spec,
                 const char *event_spec2,
                 const char *db_name,
                 const char *trigger);

/*
  Connections structures and functions
*/

BCError bc_prepare_sockets (void);

typedef struct BCConnection {
  BCNode node;
  BCInteger bandwidth_quality;
  BCInteger ping;
  BCInteger storage_quality;
  BCInteger availability;
  BCInteger service_quality;
  char address[0]; /* null terminated */
} BCConnection;

extern BCConnection *bc_Connections;
extern int n_Connections;

#endif /* _BITCLOUD_H */
