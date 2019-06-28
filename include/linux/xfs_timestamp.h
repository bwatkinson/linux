////////////////////////////////////
// Brian A. Added this file
////////////////////////////////////

/*
 * This header file defines three macros:
 * STATIC_LIST_CAP : Total number of timestamps to collect for all PID's
 * STATIC_PID_CAP  : Total number of PID's to collect timstamps for
 * STATIC_COL_CAP  : Timestamps per PID (This values should NEVER be adjusted!)
 *
 * Only the STATIC_LIST_CAP and STATIC_PID_CAP values should be adjusted to
 * change the total number of timestmaps to collect in total and the total
 * number of PID's to collect timestamps for.
 */ 

#ifndef _XFS_TIMESTAMP_H
#define _XFS_TIMESTAMP_H

#include <linux/module.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

/*
 * Change this variable in order to collect a hard set number of
 * total timestamps for all PID's
 */
#define STATIC_LIST_CAP 110000

/*
 * Change this variable in order to watch a set number of PID's
 */
#define STATIC_PID_CAP 256

/*
 * For each row for a PID the first number is the PID and the
 * second is the current offset into the row hence + 2
 */
#define STATIC_COL_CAP (STATIC_LIST_CAP + 2)

typedef long long longlong_t;

#define SEC      1
#define MILLISEC 1000
#define MICROSEC 1000000
#define NANOSEC  1000000000

#define MSEC2NSEC(m) ((longlong_t)(m) * (NANOSEC / MILLISEC))
#define NSEC2MSEC(n) ((n) / (NANOSEC / MILLISEC))

#define USEC2NSEC(m) ((longlong_t)(m) * (NANOSEC / MICROSEC))
#define NSEC2USEC(n) ((n) / (NANOSEC / MICROSEC))

#define NSEC2SEC(n)  ((n) / (NANOSEC / SEC))
#define SEC2NSEC(m)  ((longlong_t)(m) * (NANOSEC / SEC))

#define xfs_filp_close(f) filp_close(f, NULL)

typedef struct ts_array_s
{
    longlong_t array[STATIC_PID_CAP][STATIC_COL_CAP];
    int dumped;
    int array_size;
    longlong_t total_pids;
    int row_select_iter;
    struct file *dump_file;
    loff_t file_offset;
} ts_array_t;

/************ Function Declartion ******************/
void xfs_add_timestamp(int curr_pid, unsigned int offset, const char *call_site_name);

#endif /* _XFS_TIMESTAMP_H */
