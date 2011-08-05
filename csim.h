/*----------------------------------------------------------------------------*/
/*   Portions of CSIM are copyrighted by                                      */
/*   Microelectronics and Computer Technology Corporation, 1987.              */
/*   1988, 1989, 1990, 1991, 1992                                             */	
/*   All rights are reserved.                                                 */
/*----------------------------------------------------------------------------*/

/*   This header file uses ints instead of booleans to avoid defining the     */
/*   type boolean in user programs.                                           */

#ifndef _CSIM_H
#define _CSIM_H
#include <stdio.h>

/*	can define this or not */

#define terminate csim_terminate
#define random csim_random_int
#ifndef __cpluscplus
#define random_int csim_random_int
#endif
#define clock csim_clock

#define rerun() csim_rerun()
#define reset() csim_reset()

#ifndef __cplusplus

#define mailbox(name) create_mailbox(name)
#define global_mailbox(name) create_global_mailbox(name)
#define mailbox_set(arr, name, n) create_mailbox_set(arr, name, n)
#define send(mb, msg) csim_send(mb, msg)
#define receive(mb, msg) csim_receive(mb, msg)

#define facility(name) create_facility(name)
#define facility_set(arr, name, len) create_facility_set(arr, name, len)
#define facility_ms(name,num) create_facility_ms(name,num)
#define status(x) csim_status(x)

#define storage(name,amt) create_storage(name,amt)
#define storage_set(arr,name,size,n) create_storage_set(arr,name,size,n)
#define buffer(name, size) create_buffer(name, size);

#define event(name) create_event(name)
#define global_event(name) create_global_event(name)
#define event_set(arr,name,n) create_event_set(arr,name,n)
#define wait(x) csim_wait(x)
#define queue(x) csim_queue(x)
#define set(x) csim_set(x)
#define clear(x) csim_clear(x)
#define state(x) csim_state(x)
#define identity() csim_identity()
#define priority() csim_priority()

#define process_class(name) create_process_class(name)

#define csim_random(x, y) csim_random_int(x, y)

#define table(name) create_table(name)
#define permanent_table(name) create_permanent_table(name)

#define histogram(name,n,low,high) create_old_histogram(name,n,low,high)
#define permanent_histogram(name,n,low,high) create_permanent_histogram(name,n,low,high)

#define qtable(name) create_qtable(name)

#define qhistogram(name,n) create_qhistogram(name,n)

#define meter(name) create_meter(name)

#define box(name) create_box(name)
#endif
/*	specify better random number generator */
/* #define BETTER_RAND */

/*  specify option to use priority in next event list (in case of ties) */
/* #define HOLD_PRI */

#ifdef __cplusplus
#ifndef __STDC__
#define __STDC__ 1  /* jorgeg - comment this out for VACPP95 C++ Version */
#endif
#endif

/* #ifndef SOLARIS */ /* jorgeg - from solar86,solaris*/
#ifndef __STDC__
/* #define __STDC__ 0 */ /* jorgeg - comment this out for VACPP95 C++ Version
		    alpha  solar86 solaris sunos sgi and hpgnu*/
/* #define __STDC__ */
#endif
/* #endif *//* solaris */ /* jorgeg from solar86 solaris */
/* jorgeg - for sunos uncomment the following */
/*
#ifdef EXTERN_FUNCTION
#undef EXTERN_FUNCTION
#endif
#ifdef _VOID_
#undef _VOID_
#endif
*/

/* jorgeg - uncomment the following  for VACPP95 C++ Version SOLAR86 SOLARIS SUNOS and RS6000*/
/* #ifdef __cplusplus
   #define EXTERN_FUNCTION( rtn, args ) extern "C" { rtn args; }
   #define _VOID_ void
   #include <stdio.h>
   #else */
#ifdef __STDC__   /* jorgeg  ifdef for hpgnu*/
#define EXTERN_FUNCTION( rtn, args ) rtn args
#define _VOID_ void
/*#include <stdio.h> */
#else
/*#define EXTERN_FUNCTION( rtn, args ) rtn args
  #define _VOID_ void
  #include <stdio.h>
*/ 
/* jorgeg - replace the following with the above for VACPP95 */
#define EXTERN_FUNCTION( rtn, args ) rtn()
#define _VOID_ 

#endif
/* #endif */ /* jorgeg - uncomment this for VACPP95 C++ Version SOLAR86 SOLARIS SUNOSand RS6000 BCW*/

/* #ifndef _WINDOWS_
typedef char boolean;
#endif */

#define NIL	0l

#define TIMED_OUT -1l
#define EVENT_OCCURRED 4l

#define ON      0l
#define OFF     1l
#define DET     2l

/*----------------------------------------------------------------------------*/
/*   Processes / simulation time / event list                                 */
/*----------------------------------------------------------------------------*/

#ifndef META
//#ifndef CSIM18
#ifndef CSIM18
#define create(nm) if(x_create(nm)) return
#else
#define create(nm) if(x_create(nm)) return _newPid
#endif
#else                   /* force NCR compiler to generate stack frames */
EXTERN_FUNCTION( void xjunk, (long*) );
#define create(nm) {long xxjunk; xjunk(&xxjunk);} if(x_create(nm)) return
#endif
#define create_ctl(nm) \
	make_ctrl_proc = ON; \
	create(nm);

EXTERN_FUNCTION( long  x_create, (const char*) );
EXTERN_FUNCTION( void  enable_separate_stacks, (long) );
EXTERN_FUNCTION( void  csim_terminate, (_VOID_) );
EXTERN_FUNCTION( void  set_priority, (long) );
EXTERN_FUNCTION( char* process_name, (_VOID_) );
EXTERN_FUNCTION( long  csim_identity, (_VOID_) );
EXTERN_FUNCTION( long  csim_priority, (_VOID_) );
EXTERN_FUNCTION( long  max_processes, (long) );
EXTERN_FUNCTION( void  status_processes, (_VOID_) );
EXTERN_FUNCTION( void  status_next_event_list, (_VOID_) );

typedef double TIME;
EXTERN_FUNCTION( TIME  simtime, (_VOID_) );
extern TIME clock;
EXTERN_FUNCTION( void  hold, (double) );

/*----------------------------------------------------------------------------*/
/*   Process classes                                                          */
/*----------------------------------------------------------------------------*/

typedef struct clss * CLASS;
/* typedef CLASS process_class_t;  */

#ifdef CPP /* || __cplusplus */ /* jorgeg - hpgnu version does not define CPP
			      so i added || __cplusplus */
/* #define process_class(name,pc) create_process_class(name, pc) */
EXTERN_FUNCTION( CLASS create_process_class, (const char*, void*) );
EXTERN_FUNCTION( CLASS create_process_class_perm, (const char*, void*) );
/* jorgeg - for hpgnu replace with 
EXTERN_FUNCTION( CLASS create_process_class, (const char*, process_class_t) );*/
#else
#ifndef CPP /* || __cplusplus */ /* jorgeg - hpgnu version does not define CPP
			      so i added || __cplusplus */
#endif
EXTERN_FUNCTION( CLASS  create_process_class, (const char*) );
EXTERN_FUNCTION( CLASS  create_process_class_perm, (const char*) );
#endif

EXTERN_FUNCTION( void   set_name_process_class, (CLASS, const char*) );
EXTERN_FUNCTION( void   delete_process_class, (CLASS) );
EXTERN_FUNCTION( void   set_process_class, (CLASS) );
EXTERN_FUNCTION( void	reset_process_class, (CLASS) );
EXTERN_FUNCTION( void	reset_process_classes, (_VOID_) );

#ifdef CPP /* || __cplusplus */  /* jorgeg - hpgnu version does not define CPP
			      so i added || __cplusplus */
EXTERN_FUNCTION( void* xcurrent_class, (_VOID_) );
/* jorgeg - for hpgnu replace with 
EXTERN_FUNCTION( process_class_t current_class, (_VOID_) );*/
#else
EXTERN_FUNCTION( CLASS current_class, (_VOID_) );
#endif

EXTERN_FUNCTION( long   class_id, (CLASS) );
EXTERN_FUNCTION( char*	class_name, (CLASS) );
EXTERN_FUNCTION( long   class_cnt, (CLASS) );
EXTERN_FUNCTION( double class_lifetime, (CLASS) );
EXTERN_FUNCTION( long   class_holdcnt, (CLASS) );
EXTERN_FUNCTION( double class_holdtime, (CLASS) );
EXTERN_FUNCTION( long   max_classes, (long) );
EXTERN_FUNCTION( void   report_classes, (_VOID_) );

/*----------------------------------------------------------------------------*/
/*	CSIM Processes															  */
/*----------------------------------------------------------------------------*/

typedef struct pcb *PROCESS;
typedef struct q_elem *PROCESS_PTR;

EXTERN_FUNCTION( PROCESS_PTR next_process, (PROCESS_PTR) );
EXTERN_FUNCTION( long get_process_priority, (PROCESS_PTR) );
EXTERN_FUNCTION( void set_process_priority, (PROCESS_PTR, long) );
EXTERN_FUNCTION( long get_process_identity, (PROCESS_PTR) );
EXTERN_FUNCTION( char* get_process_name, (PROCESS_PTR) );
EXTERN_FUNCTION( void* get_process_struct, (PROCESS_PTR) );
EXTERN_FUNCTION( void set_process_struct, (PROCESS_PTR, void*) );
EXTERN_FUNCTION( void set_this_struct, (void *) );
EXTERN_FUNCTION( void* get_this_struct, (_VOID_) );
EXTERN_FUNCTION( void restart_process, (PROCESS_PTR) );
EXTERN_FUNCTION( PROCESS_PTR this_process, (_VOID_) );

/*----------------------------------------------------------------------------*/
/*   Queue statistics collecdtor                                              */
/*----------------------------------------------------------------------------*/

typedef struct queue_stat *QUEUE_STAT;

EXTERN_FUNCTION( QUEUE_STAT create_queue_stat, (const char *nm) );
EXTERN_FUNCTION( void delete_queue_stat, (QUEUE_STAT qs) );
EXTERN_FUNCTION( void queue_stat_join, (QUEUE_STAT qs) );
EXTERN_FUNCTION( void queue_stat_leave, (QUEUE_STAT qs) );
EXTERN_FUNCTION( void queue_stat_report, (QUEUE_STAT qs) );
EXTERN_FUNCTION( double queue_stat_resp, (QUEUE_STAT qs) );
EXTERN_FUNCTION( double queue_stat_qlen, (QUEUE_STAT qs) );
EXTERN_FUNCTION( double queue_stat_sumq, (QUEUE_STAT qs) );
EXTERN_FUNCTION( long queue_stat_departures, (QUEUE_STAT qs) );
EXTERN_FUNCTION( long queue_stat_current_count, (QUEUE_STAT qs) );
EXTERN_FUNCTION( double queue_stat_elapsed_time, (QUEUE_STAT qs) );

/*----------------------------------------------------------------------------*/
/*   Facilities                                                               */
/*----------------------------------------------------------------------------*/

typedef struct fac *FACILITY;
#define BUSY 1l
#define FREE 0l

#ifdef __STDC__  /* jorgeg - ifdef for hpgnu */ /* jorgeg - #ifdef CPP for RS6000 #ifdef __cplusplus* for sunos */
typedef void (*SF)(FACILITY, double);     /* facility service function */
#else
typedef void (*SF)();
#endif

typedef struct evnt *EVENT;

EXTERN_FUNCTION( FACILITY create_facility, (const char*) );
EXTERN_FUNCTION( void   create_facility_set, (FACILITY*, const char*, long) );
EXTERN_FUNCTION( FACILITY create_facility_ms, (const char*, long) );
EXTERN_FUNCTION( void   set_name_facility, (FACILITY, const char*) );
EXTERN_FUNCTION( void   collect_class_facility, (FACILITY) );
EXTERN_FUNCTION( void   collect_class_facility_all, (_VOID_) );
EXTERN_FUNCTION( void   delete_facility, (FACILITY) );
EXTERN_FUNCTION( void   delete_facility_set, (FACILITY*) );
EXTERN_FUNCTION( long   reserve, (FACILITY) );
EXTERN_FUNCTION( long   timed_reserve, (FACILITY, double) );
EXTERN_FUNCTION( void   release, (FACILITY) );
EXTERN_FUNCTION( void   release_server, (FACILITY, long) );
EXTERN_FUNCTION( TIME   use, (FACILITY, double) );
EXTERN_FUNCTION( void   set_servicefunc, (FACILITY, SF) );
EXTERN_FUNCTION( void   fcfs, (FACILITY, double) );
EXTERN_FUNCTION( void   fcfs_sy, (FACILITY, double) );
EXTERN_FUNCTION( void   inf_srv, (FACILITY, double) );
EXTERN_FUNCTION( void   lcfs_pr, (FACILITY, double) );
EXTERN_FUNCTION( void   prc_shr, (FACILITY, double) );
EXTERN_FUNCTION( void   pre_res, (FACILITY, double) );
EXTERN_FUNCTION( void	pre_rst, (FACILITY, double) );
EXTERN_FUNCTION( void	rnd_pre, (FACILITY, double) );
EXTERN_FUNCTION( void   rnd_pri, (FACILITY, double) );
EXTERN_FUNCTION( void   rnd_rob, (FACILITY, double) );
EXTERN_FUNCTION( void   synchronous_facility, (FACILITY, double, double) );
EXTERN_FUNCTION( void   set_loaddep, (FACILITY, double*, long) );
EXTERN_FUNCTION( void   set_timeslice, (FACILITY, double) );
EXTERN_FUNCTION( char*	facility_name, (FACILITY) );
EXTERN_FUNCTION( long   num_servers, (FACILITY) );
EXTERN_FUNCTION( char*	service_disp, (FACILITY) );
EXTERN_FUNCTION( double timeslice, (FACILITY) );
EXTERN_FUNCTION( long   num_busy, (FACILITY) );
EXTERN_FUNCTION( long   qlength, (FACILITY) );
EXTERN_FUNCTION( long   csim_status, (FACILITY) );
EXTERN_FUNCTION( long   completions, (FACILITY) );
EXTERN_FUNCTION( long   preempts, (FACILITY) );
EXTERN_FUNCTION( double qlen, (FACILITY) );
EXTERN_FUNCTION( double resp, (FACILITY) );
EXTERN_FUNCTION( double serv, (FACILITY) );
EXTERN_FUNCTION( double tput, (FACILITY) );
EXTERN_FUNCTION( double util, (FACILITY) );
EXTERN_FUNCTION( long   server_completions, (FACILITY, long) );
EXTERN_FUNCTION( double server_serv, (FACILITY, long) );
EXTERN_FUNCTION( double server_tput, (FACILITY, long) );
EXTERN_FUNCTION( double server_util, (FACILITY, long) );
EXTERN_FUNCTION( long	class_qlength, (FACILITY, CLASS) );
EXTERN_FUNCTION( long   class_completions, (FACILITY, CLASS) );
EXTERN_FUNCTION( double class_qlen, (FACILITY, CLASS) );
EXTERN_FUNCTION( double class_resp, (FACILITY, CLASS) );
EXTERN_FUNCTION( double class_serv, (FACILITY, CLASS) );
EXTERN_FUNCTION( double class_tput, (FACILITY, CLASS) );
EXTERN_FUNCTION( double class_util, (FACILITY, CLASS) );
EXTERN_FUNCTION( long   max_facilities, (long) );
EXTERN_FUNCTION( long   max_servers, (long) );
EXTERN_FUNCTION( void   status_facilities, (_VOID_) );
EXTERN_FUNCTION( void   report_facilities, (_VOID_) );
EXTERN_FUNCTION( void	reset_facility, (FACILITY) );
EXTERN_FUNCTION( void	reset_facilities, (_VOID_) );

EXTERN_FUNCTION( PROCESS_PTR facility_first_process, (FACILITY) );
EXTERN_FUNCTION( PROCESS_PTR facility_last_process, (FACILITY) );
EXTERN_FUNCTION( PROCESS_PTR facility_remove_process, (FACILITY, PROCESS_PTR) );
EXTERN_FUNCTION( void facility_insert_process, (FACILITY, PROCESS_PTR) );

/*----------------------------------------------------------------------------*/
/*   Storages                                                                 */
/*----------------------------------------------------------------------------*/

typedef struct store * STORE;

EXTERN_FUNCTION( STORE  create_storage, (const char*, long) );
EXTERN_FUNCTION( void   create_storage_set, (STORE*, const char*, long, long) );
EXTERN_FUNCTION( void   set_name_storage, (STORE, const char*) );
EXTERN_FUNCTION( void   delete_storage, (STORE) );
EXTERN_FUNCTION( void   delete_storage_set, (STORE*) );
EXTERN_FUNCTION( void   allocate, (long, STORE) );
EXTERN_FUNCTION( void	alloc, (STORE, long) );
EXTERN_FUNCTION( long   timed_allocate, (long, STORE, double) );
EXTERN_FUNCTION( long	timed_alloc, (STORE, long, double) );
EXTERN_FUNCTION( void   deallocate, (long, STORE) );
EXTERN_FUNCTION( void	dealloc, (STORE, long) );
EXTERN_FUNCTION( void   add_store, (long, STORE) );
EXTERN_FUNCTION( void	add_more_store, (STORE, long) );
EXTERN_FUNCTION( void	remove_store, (STORE, long) );
EXTERN_FUNCTION( void   synchronous_storage, (STORE, double, double) );
EXTERN_FUNCTION( char*	storage_name, (STORE) );
EXTERN_FUNCTION( long   storage_capacity, (STORE) );
EXTERN_FUNCTION( long   avail, (STORE) );
EXTERN_FUNCTION( double storage_request_amt, (STORE) );
EXTERN_FUNCTION( double   storage_request_total, (STORE) );
EXTERN_FUNCTION( double   storage_release_total, (STORE) );
EXTERN_FUNCTION( long   storage_number_amt, (STORE) );
EXTERN_FUNCTION( TIME   storage_busy_amt, (STORE) );
EXTERN_FUNCTION( TIME   storage_waiting_amt, (STORE) );
EXTERN_FUNCTION( long   storage_request_cnt, (STORE) );
EXTERN_FUNCTION( long   storage_release_cnt, (STORE) );
EXTERN_FUNCTION( long   storage_queue_cnt, (STORE) );
EXTERN_FUNCTION( long   storage_qlength, (STORE) );
EXTERN_FUNCTION( double storage_time, (STORE) );
EXTERN_FUNCTION( void   status_storages, (_VOID_) );
EXTERN_FUNCTION( long   max_storages, (long) );
EXTERN_FUNCTION( void   report_storages, (_VOID_) );
EXTERN_FUNCTION( void	reset_storage, (STORE) );
EXTERN_FUNCTION( void	reset_storages, (_VOID_) );

EXTERN_FUNCTION( PROCESS_PTR storage_first_process, (STORE) );
EXTERN_FUNCTION( PROCESS_PTR storage_last_process, (STORE) );
EXTERN_FUNCTION( PROCESS_PTR storage_remove_process, (STORE, PROCESS_PTR) );
EXTERN_FUNCTION( void storage_insert_process, (STORE, PROCESS_PTR) );

/*----------------------------------------------------------------------------*/
/*   Buffers                                                                  */
/*----------------------------------------------------------------------------*/

typedef struct bufr *BUFFER;

EXTERN_FUNCTION( BUFFER create_buffer, (const char *nm, const long sz) );
EXTERN_FUNCTION( void delete_buffer, (BUFFER b) );
EXTERN_FUNCTION( void buffer_put, (BUFFER b, const long amt) );
EXTERN_FUNCTION( void buffer_get, (BUFFER b, const long amt) );
EXTERN_FUNCTION( long buffer_timed_put, (BUFFER b, const long amt, const double t) );
EXTERN_FUNCTION( long buffer_timed_get, (BUFFER b, const long amt, const double t) );
EXTERN_FUNCTION( long buffer_current, (BUFFER b) );
EXTERN_FUNCTION( long buffer_size, (BUFFER b) );
EXTERN_FUNCTION( long buffer_get_total, (BUFFER b) );
EXTERN_FUNCTION( long buffer_put_total, (BUFFER b) );
EXTERN_FUNCTION( long buffer_get_count, (BUFFER b) );
EXTERN_FUNCTION( long buffer_put_count, (BUFFER b) );
EXTERN_FUNCTION( double buffer_get_timeQueue, (BUFFER b) );
EXTERN_FUNCTION( double buffer_put_timeQueue, (BUFFER b) );
EXTERN_FUNCTION( void buffer_add_space, (BUFFER b, const long amt) );
EXTERN_FUNCTION( void buffer_remove_space, (BUFFER b, const long amt) );
EXTERN_FUNCTION( char* buffer_name, (BUFFER b) );
EXTERN_FUNCTION( long buffer_get_current_count, (BUFFER b) );
EXTERN_FUNCTION( long buffer_put_current_count, (BUFFER b) );
EXTERN_FUNCTION( PROCESS_PTR buffer_put_first_process, (BUFFER b) );
EXTERN_FUNCTION( PROCESS_PTR buffer_put_last_process, (BUFFER b) );
EXTERN_FUNCTION( PROCESS_PTR buffer_put_remove_process, (BUFFER b, PROCESS_PTR p) );
EXTERN_FUNCTION( void buffer_put_insert_process, (BUFFER b, PROCESS_PTR p) );
EXTERN_FUNCTION( PROCESS_PTR buffer_get_first_process, (BUFFER b) );
EXTERN_FUNCTION( PROCESS_PTR buffer_get_last_process, (BUFFER b) );
EXTERN_FUNCTION( PROCESS_PTR buffer_get_remove_process, (BUFFER b, PROCESS_PTR p) );
EXTERN_FUNCTION( void buffer_get_insert_process, (BUFFER b, PROCESS_PTR p) );
EXTERN_FUNCTION( QUEUE_STAT buffer_get_queue_stat, (BUFFER b) );
EXTERN_FUNCTION( QUEUE_STAT buffer_put_queue_stat, (BUFFER b) );
EXTERN_FUNCTION( void report_buffers, (_VOID_) );
EXTERN_FUNCTION( void reset_buffer, (BUFFER b) );
EXTERN_FUNCTION( void reset_buffers, (_VOID_) );
EXTERN_FUNCTION( long max_buffers, (long) );
EXTERN_FUNCTION( void status_buffers, (_VOID_) );

/*----------------------------------------------------------------------------*/
/*   Events                                                                   */
/*----------------------------------------------------------------------------*/

#define OCC 1l
#define NOT_OCC 2l

EXTERN_FUNCTION( EVENT  create_event , (const char*) );
EXTERN_FUNCTION( EVENT  create_global_event, (const char*) );
EXTERN_FUNCTION( void   create_event_set, (EVENT*, const char*, long) );
EXTERN_FUNCTION( void   set_name_event, (EVENT, const char*) );
EXTERN_FUNCTION( const  char* event_name, (EVENT) );
EXTERN_FUNCTION( const	char* event_set_name, (EVENT*) );
EXTERN_FUNCTION( void   delete_event, (EVENT) );
EXTERN_FUNCTION( void   delete_event_set, (EVENT*) );
EXTERN_FUNCTION( void	report_events, (_VOID_) );
EXTERN_FUNCTION( void	event_monitor, (EVENT) );
EXTERN_FUNCTION( void	reset_event, (EVENT) );
EXTERN_FUNCTION( void	reset_events, (_VOID_) );

EXTERN_FUNCTION( void   csim_wait, (EVENT) );
EXTERN_FUNCTION( long   wait_any, (EVENT*) );
EXTERN_FUNCTION( long   timed_wait, (EVENT, double) );
EXTERN_FUNCTION( long	timed_wait_any, (EVENT*, double) );
EXTERN_FUNCTION( void   csim_queue, (EVENT) );
EXTERN_FUNCTION( long   queue_any, (EVENT*) );
EXTERN_FUNCTION( long   timed_queue, (EVENT, double) );
EXTERN_FUNCTION( long	timed_queue_any, (EVENT*, double) );
EXTERN_FUNCTION( void   csim_set, (EVENT) );
EXTERN_FUNCTION( void   csim_clear, (EVENT) );
EXTERN_FUNCTION( long   wait_cnt, (EVENT) );
EXTERN_FUNCTION( long   queue_cnt, (EVENT) );
EXTERN_FUNCTION( long   event_qlen, (EVENT) );
EXTERN_FUNCTION( long   csim_state, (EVENT) );
EXTERN_FUNCTION( long   max_events, (long) );
EXTERN_FUNCTION( long	num_events, (EVENT*) );
EXTERN_FUNCTION( void   status_events, (_VOID_) );
EXTERN_FUNCTION( void	event_monitor, (EVENT ev) );
EXTERN_FUNCTION( void	event_set_monitor, (EVENT *evs) );
EXTERN_FUNCTION( EVENT	event_set_event, (EVENT *evs) );
EXTERN_FUNCTION( double	event_queue_sum, (EVENT ev) );
EXTERN_FUNCTION( double	event_wait_sum, (EVENT ev) );
EXTERN_FUNCTION( long	event_queue_delay_count, (EVENT ev) );
EXTERN_FUNCTION( long	event_wait_delay_count, (EVENT ev) );
EXTERN_FUNCTION( double	event_queue_length, (EVENT ev) );
EXTERN_FUNCTION( double	event_wait_length, (EVENT ev) );
EXTERN_FUNCTION( double	event_queue_time, (EVENT ev) );
EXTERN_FUNCTION( double	event_wait_time, (EVENT ev) );
EXTERN_FUNCTION( long	event_queue_count, (EVENT ev) );
EXTERN_FUNCTION( long	event_wait_count, (EVENT ev) );
EXTERN_FUNCTION( long	event_set_count, (EVENT ev) );

EXTERN_FUNCTION( PROCESS_PTR event_first_wait_process, (EVENT) );
EXTERN_FUNCTION( PROCESS_PTR event_last_wait_process, (EVENT) );
EXTERN_FUNCTION( PROCESS_PTR event_remove_wait_process, (EVENT, PROCESS_PTR) );
EXTERN_FUNCTION( void event_insert_wait_process, (EVENT, PROCESS_PTR) );

EXTERN_FUNCTION( PROCESS_PTR event_first_queue_process, (EVENT) );
EXTERN_FUNCTION( PROCESS_PTR event_last_queue_process, (EVENT) );
EXTERN_FUNCTION( PROCESS_PTR event_remove_queue_process, (EVENT, PROCESS_PTR) );
EXTERN_FUNCTION( void event_insert_queue_process, (EVENT, PROCESS_PTR) );	

/*----------------------------------------------------------------------------*/
/*	CSIM message															  */
/*----------------------------------------------------------------------------*/

typedef struct msg_s *MSG_PTR;

EXTERN_FUNCTION( MSG_PTR next_msg, (MSG_PTR) );
EXTERN_FUNCTION( long msg_content, (MSG_PTR) );		

/*----------------------------------------------------------------------------*/
/*   Mailboxs                                                                 */
/*----------------------------------------------------------------------------*/

typedef struct mbox *MBOX;

EXTERN_FUNCTION( MBOX   create_mailbox, (const char*) );
EXTERN_FUNCTION( MBOX	create_global_mailbox, (const char*) );
EXTERN_FUNCTION( void   set_name_mailbox, (MBOX, const char*) );
EXTERN_FUNCTION( void   delete_mailbox, (MBOX) );
EXTERN_FUNCTION( void   csim_send, (MBOX, long) );
EXTERN_FUNCTION( void	synchronous_send, (MBOX, long) );
EXTERN_FUNCTION( long	timed_synchronous_send, (MBOX, long, double) );
EXTERN_FUNCTION( void   csim_receive, (MBOX, long*) );
EXTERN_FUNCTION( long   timed_receive, (MBOX, long*, double) );
EXTERN_FUNCTION( long   msg_cnt, (MBOX) );
EXTERN_FUNCTION( long	mailbox_queue_cnt, (MBOX) );
EXTERN_FUNCTION( char*	mailbox_name, (MBOX) );
EXTERN_FUNCTION( long   max_mailboxes, (long) );
EXTERN_FUNCTION( long   max_messages, (long) );
EXTERN_FUNCTION( void   status_mailboxes, (_VOID_) );

EXTERN_FUNCTION( double mailbox_proc_sum, (MBOX) );
EXTERN_FUNCTION( long mailbox_proc_delay_count, (MBOX) );
EXTERN_FUNCTION( long mailbox_proc_count, (MBOX) );
EXTERN_FUNCTION( double mailbox_proc_length, (MBOX) );
EXTERN_FUNCTION( double mailbox_proc_time, (MBOX) );
EXTERN_FUNCTION( double mailbox_msg_sum, (MBOX) );
EXTERN_FUNCTION( long mailbox_msg_delay_count, (MBOX) );
EXTERN_FUNCTION( long mailbox_msg_count, (MBOX) );
EXTERN_FUNCTION( double mailbox_msg_length, (MBOX) );
EXTERN_FUNCTION( double mailbox_msg_time, (MBOX) );
EXTERN_FUNCTION( void mailbox_monitor, (MBOX) );
EXTERN_FUNCTION( void report_mailboxes, (_VOID_));
EXTERN_FUNCTION( void reset_mailbox, (MBOX) );
EXTERN_FUNCTION( void reset_mailboxes, (_VOID_) );

EXTERN_FUNCTION( void create_mailbox_set, (MBOX*, const char*, long) );
EXTERN_FUNCTION( const char* mailbox_set_name, (MBOX*) );
EXTERN_FUNCTION( long mailbox_set_num_msgs, (MBOX*) );
EXTERN_FUNCTION( EVENT mailbox_set_event, (MBOX*) );
EXTERN_FUNCTION( void mailbox_set_monitor, (MBOX*) );
EXTERN_FUNCTION( void delete_mailbox_set, (MBOX*) );
EXTERN_FUNCTION( long receive_any, (MBOX*, long*) );
EXTERN_FUNCTION( long timed_receive_any, (MBOX*, long*, double) );

EXTERN_FUNCTION( PROCESS_PTR mailbox_first_process, (MBOX) );
EXTERN_FUNCTION( PROCESS_PTR mailbox_last_process, (MBOX) );
EXTERN_FUNCTION( PROCESS_PTR mailbox_remove_process, (MBOX, PROCESS_PTR) );
EXTERN_FUNCTION( void mailbox_insert_process, (MBOX, PROCESS_PTR) );

EXTERN_FUNCTION( MSG_PTR mailbox_first_msg, (MBOX) );
EXTERN_FUNCTION( MSG_PTR mailbox_last_msg, (MBOX) );
EXTERN_FUNCTION( MSG_PTR mailbox_remove_msg, (MBOX, MSG_PTR) );
EXTERN_FUNCTION( void mailbox_insert_msg, (MBOX, MSG_PTR) );	

/*----------------------------------------------------------------------------*/
/*   Random number generation                                                 */
/*----------------------------------------------------------------------------*/

typedef struct strm1 * STREAM1;
typedef struct strm2 * STREAM2;
typedef double (*SP)(void*);
typedef double (*SP1)(STREAM1);
typedef double (*SP2)(STREAM2);

#ifndef BETTER_RAND
#define get_seed()	stream_state1(NIL)
#define STREAM void*
#define create_stream	create_stream1
#define stream_state	stream_state1
#define reseed			reseed1
#define delete_stream	delete_stream1
#define reset_prob		reset_prob1
#define stream_reset_prob	stream_reset_prob1
/* #define stream_prob		stream_prob1 */
#else
#define get_seed(n1, n2) stream_state2(NIL, n1, n2 );
#define STREAM STREAM2
#define create_stream	create_stream2
#define reseed			reseed2
#define delete_stream	delete_stream2
#define reset_prob		reset_prob2
#define stream_reset_prob	stream_reset_prob2
/* #define stream_prob		stream_prob2 */
#endif

EXTERN_FUNCTION( long	stream_state1, (STREAM1) );
EXTERN_FUNCTION( void	stream_state2, (STREAM2, long*, long *) );
EXTERN_FUNCTION( double stream_prob1, (STREAM1) );
EXTERN_FUNCTION( double stream_prob2, (STREAM2) );
/* EXTERN_FUNCTION( STREAM create_stream, (_VOID_) ); */
EXTERN_FUNCTION( STREAM1 create_stream1, (_VOID_) );
EXTERN_FUNCTION( STREAM2 create_stream2, (_VOID_) );
EXTERN_FUNCTION( void   reseed1, (STREAM1, long) );
EXTERN_FUNCTION( void   reseed2, (STREAM2, long, long) );
EXTERN_FUNCTION( void	delete_stream1, (STREAM1) );
EXTERN_FUNCTION( void	delete_stream2, (STREAM2) );
/* EXTERN_FUNCTION( double stream_prob, (void*) ); */
EXTERN_FUNCTION( void	set_stream_prob, (SP) );
EXTERN_FUNCTION( void	set_stream_prob1, (SP1) );
EXTERN_FUNCTION( void	set_stream_prob2, (SP2) );

#ifndef __cplusplus
#define stream()				 create_stream1()
#define prob()                   stream_prob(NIL)
#define uniform01()              stream_uniform01(NIL)
#define uniform(mn,mx)			 stream_uniform(NIL,mn,mx)
#define triangular(mn,mx,mode)	 stream_triangular(NIL,mn,mx,mode)
#define gamma(mean,stddev)       stream_gamma(NIL,mean,stddev)
#define expntl(mean)             stream_exponential(NIL,mean)
#define exponential(mean)        stream_exponential(NIL,mean)
#define erlang(mean,var)         stream_erlang(NIL,mean,var)
#define erlang2(mean,var)        stream_erlang2(NIL,mean,var)
#define erlangn(mean, n)		 stream_elrangn(NIL, mean, n)
#define hyperx(mean,var)         stream_hyperx(NIL,mean,var)
#define beta(mn,mx,sh1,sh2)      stream_beta(NIL,mn,mx,sh1,sh2)
#define weibull(shape,scale)     stream_weibull(NIL,shape,scale)
#ifndef MAC
#ifndef MAC_PPC
#define normal(mean,stddev)      stream_normal(NIL,mean,stddev)
#else
#define x_normal(mean,stddev)    stream_normal(NIL,mean,stddev)
#endif
#else
#define x_normal(mean,stddev)    	 stream_normal(NIL,mean,stddev)
#endif
#define normal2(mean,stddev)     stream_normal2(NIL,mean,stddev)
#define lognormal(mean,stddev)   stream_lognormal(NIL,mean,stddev)
#define cauchy(alpha,beta)       stream_cauchy(NIL,alpha,beta)
#define hypoexponential(mn, vr)	 stream_hypoexponential(NIL, mn, vr)
#define pareto(a)				 stream_pareto(NIL, a)
#define zipf(n)					 stream_zipf(NIL, n)
#define zipf_sum(n, sum)		 stream_zipf_sum(NIL, n, sum)
#define csim_random_int(mn,mx)	 stream_uniform_int(NIL,mn,mx)
#define uniform_int(mn,mx)		 stream_uniform_int(NIL,mn,mx)
#define bernoulli(ps)            stream_bernoulli(NIL,ps)
#define binomial(ps,nt)          stream_binomial(NIL,ps,nt)
#define geometric(ps)            stream_geometric(NIL,ps)
#define negative_binomial(sn,ps) stream_negative_binomial(NIL,sn,ps)
#define poisson(mean)            stream_poisson(NIL,mean)
#define empirical(n,cut,als,val) stream_empirical(NIL,n,cut,als,val)
#endif
#define stream_expntl stream_exponential
#define stream_random_int(s, mn, mx) stream_uniform_int(s, mn, mx)

EXTERN_FUNCTION( double stream_prob, (STREAM) );
EXTERN_FUNCTION( double stream_uniform01, (STREAM) );
EXTERN_FUNCTION( double stream_uniform, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_triangular, (STREAM, double, double, double) );
EXTERN_FUNCTION( double stream_gamma, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_exponential, (STREAM, double) );
EXTERN_FUNCTION( double stream_erlang, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_erlang2, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_erlangn, (STREAM, double, long) );
EXTERN_FUNCTION( double stream_hyperx, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_beta, (STREAM, double, double, double, double) );
EXTERN_FUNCTION( double stream_weibull, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_normal, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_normal2, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_lognormal, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_cauchy, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_hypoexponential, (STREAM, double, double) );
EXTERN_FUNCTION( double stream_pareto, (STREAM, double) );
EXTERN_FUNCTION( long	stream_zipf, (STREAM, long) );
EXTERN_FUNCTION( long	stream_zipf_sum, (STREAM, long, double *) );
/* EXTERN_FUNCTION( long   stream_random_int, (STREAM, long, long) ); */
EXTERN_FUNCTION( long   stream_uniform_int, (STREAM, long, long) );
EXTERN_FUNCTION( long   stream_bernoulli, (STREAM, double) );
EXTERN_FUNCTION( long   stream_binomial, (STREAM, double, long) );
EXTERN_FUNCTION( long   stream_geometric, (STREAM, double) );
EXTERN_FUNCTION( long   stream_negative_binomial, (STREAM, long, double) );
EXTERN_FUNCTION( long   stream_poisson, (STREAM, double) );
EXTERN_FUNCTION( void   setup_empirical, (const long, const double*, double*, long*) );
EXTERN_FUNCTION( double stream_empirical, (STREAM, const long, double*, long*, const double*) );

/* legacy functions */

EXTERN_FUNCTION( STREAM1 stream_init1, (long) );
EXTERN_FUNCTION( void   stream_reset_prob1, (STREAM1, long) );
EXTERN_FUNCTION( void   reset_prob1, (long) );

/*----------------------------------------------------------------------------*/
/*   Tables                                                                   */
/*----------------------------------------------------------------------------*/

typedef struct tbl * TABLE;
typedef struct histo * HISTO;

EXTERN_FUNCTION( TABLE  create_table, (const char*) );
EXTERN_FUNCTION( TABLE  create_permanent_table, (const char*) );
EXTERN_FUNCTION( void   table_histogram, (TABLE, long, double, double) );
EXTERN_FUNCTION( void   table_confidence, (TABLE) );
EXTERN_FUNCTION( void   table_run_length, (TABLE, double, double, double) );
EXTERN_FUNCTION( void   table_moving_window, (TABLE, long) );
EXTERN_FUNCTION( void   record, (double, TABLE) );
EXTERN_FUNCTION( void	tabulate, (TABLE, double) );
EXTERN_FUNCTION( void   report_table, (TABLE) );
EXTERN_FUNCTION( void   report_tables, (_VOID_) );
EXTERN_FUNCTION( void   table_summary, (_VOID_) );
EXTERN_FUNCTION( void   set_name_table, (TABLE, const char*) );
EXTERN_FUNCTION( void   reset_table, (TABLE) );
EXTERN_FUNCTION( void	reset_tables, (_VOID_) );
EXTERN_FUNCTION( void   delete_table, (TABLE) );

EXTERN_FUNCTION( char*	table_name, (TABLE) );
EXTERN_FUNCTION( long   table_window_size, (TABLE) );
EXTERN_FUNCTION( long   table_cnt, (TABLE) );
EXTERN_FUNCTION( double table_min, (TABLE) );
EXTERN_FUNCTION( double table_max, (TABLE) );
EXTERN_FUNCTION( double table_sum, (TABLE) );
EXTERN_FUNCTION( double table_sum_square, (TABLE) );
EXTERN_FUNCTION( double table_mean, (TABLE) );
EXTERN_FUNCTION( double table_range, (TABLE) );
EXTERN_FUNCTION( double table_var, (TABLE) );
EXTERN_FUNCTION( double table_stddev, (TABLE) );
EXTERN_FUNCTION( double table_cv, (TABLE) );

EXTERN_FUNCTION( HISTO  table_hist, (TABLE) );
EXTERN_FUNCTION( long   table_histogram_num, (TABLE) );
EXTERN_FUNCTION( double table_histogram_low, (TABLE) );
EXTERN_FUNCTION( double table_histogram_high, (TABLE) );
EXTERN_FUNCTION( double table_histogram_width, (TABLE) );
EXTERN_FUNCTION( long   table_histogram_bucket, (TABLE, long) );
EXTERN_FUNCTION( long   table_histogram_total, (TABLE) );
EXTERN_FUNCTION( long   table_batch_size, (TABLE) );
EXTERN_FUNCTION( long   table_batch_count, (TABLE) );
EXTERN_FUNCTION( int	table_converged, (TABLE) );
EXTERN_FUNCTION( double table_conf_mean, (TABLE) );
EXTERN_FUNCTION( double table_conf_halfwidth, (TABLE, double) );
EXTERN_FUNCTION( double table_conf_lower, (TABLE, double) );
EXTERN_FUNCTION( double table_conf_upper, (TABLE, double) );
EXTERN_FUNCTION( double table_conf_accuracy, (TABLE, double) );

/*  legacy functions - prior to version 18  */

typedef struct tbl * HIST;

EXTERN_FUNCTION( HIST   create_old_histogram, (const char*, long, double, double) );
EXTERN_FUNCTION( HIST   create_permanent_histogram, (const char*, long, double, double) );
EXTERN_FUNCTION( void   set_moving_table, (TABLE, long) );
EXTERN_FUNCTION( long   max_tables, (long) );
EXTERN_FUNCTION( long   max_histograms, (long) );
EXTERN_FUNCTION( long   max_sizehist, (long) );
#define histogram_num table_histogram_num
#define histogram_low table_histogram_low
#define histogram_high table_histogram_high
#define histogram_width table_histogram_width
#define histogram_bucket table_histogram_bucket

/*----------------------------------------------------------------------------*/
/*   Qtables                                                                  */
/*----------------------------------------------------------------------------*/

typedef struct qtble * QTABLE;

EXTERN_FUNCTION( QTABLE create_qtable, (const char*) );
EXTERN_FUNCTION( void   qtable_histogram, (QTABLE, long, long, long) );
EXTERN_FUNCTION( void   qtable_confidence, (QTABLE) );
EXTERN_FUNCTION( void   qtable_run_length, (QTABLE, double, double, double) );
EXTERN_FUNCTION( void   qtable_moving_window, (QTABLE, long) );
EXTERN_FUNCTION( void   note_entry, (QTABLE) );
EXTERN_FUNCTION( void   note_exit, (QTABLE) );
EXTERN_FUNCTION( void   note_value, (QTABLE, long) );
EXTERN_FUNCTION( void	record_value, (QTABLE, double) );
EXTERN_FUNCTION( void	set_initial_value, (QTABLE, double) );
EXTERN_FUNCTION( void	report_qtable_dbl, (QTABLE) );
EXTERN_FUNCTION( void   report_qtable, (QTABLE) );
EXTERN_FUNCTION( void   report_qtables, (_VOID_) );
EXTERN_FUNCTION( void   qtable_summary, (_VOID_) );
EXTERN_FUNCTION( void   set_name_qtable, (QTABLE, const char*) );
EXTERN_FUNCTION( void   reset_qtable, (QTABLE) );
EXTERN_FUNCTION( void	reset_qtables, (_VOID_) );
EXTERN_FUNCTION( void   delete_qtable, (QTABLE) );

EXTERN_FUNCTION( char*	qtable_name, (QTABLE) );
EXTERN_FUNCTION( long   qtable_window_size, (QTABLE) );
EXTERN_FUNCTION( long   qtable_entries, (QTABLE) );
EXTERN_FUNCTION( long   qtable_exits, (QTABLE) );
EXTERN_FUNCTION( long   qtable_min, (QTABLE) );
EXTERN_FUNCTION( long   qtable_max, (QTABLE) );
EXTERN_FUNCTION( long	qtable_range, (QTABLE) );
EXTERN_FUNCTION( long   qtable_initial, (QTABLE) );
EXTERN_FUNCTION( long   qtable_current, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_entries, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_exits, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_min, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_max, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_initial, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_current, (QTABLE) );
EXTERN_FUNCTION( double qtable_sum, (QTABLE) );
EXTERN_FUNCTION( double qtable_sum_square, (QTABLE) );
EXTERN_FUNCTION( double qtable_mean, (QTABLE) );
EXTERN_FUNCTION( double qtable_dbl_range, (QTABLE) );
EXTERN_FUNCTION( double qtable_var, (QTABLE) );
EXTERN_FUNCTION( double qtable_stddev, (QTABLE) );
EXTERN_FUNCTION( double qtable_cv, (QTABLE) );
EXTERN_FUNCTION( int	qtable_converged, (QTABLE) );
EXTERN_FUNCTION( HISTO  qtable_hist, (QTABLE) );
EXTERN_FUNCTION( long   qtable_histogram_num, (QTABLE) );
EXTERN_FUNCTION( double qtable_histogram_low, (QTABLE) );
EXTERN_FUNCTION( double qtable_histogram_high, (QTABLE) );
EXTERN_FUNCTION( double qtable_histogram_width, (QTABLE) );
EXTERN_FUNCTION( double qtable_histogram_bucket, (QTABLE, long) );
EXTERN_FUNCTION( double qtable_histogram_total, (QTABLE) );
EXTERN_FUNCTION( double	qtable_batch_size, (QTABLE) );
EXTERN_FUNCTION( long   qtable_batch_count, (QTABLE) );
EXTERN_FUNCTION( double qtable_conf_mean, (QTABLE) );
EXTERN_FUNCTION( double qtable_conf_halfwidth, (QTABLE, double) );
EXTERN_FUNCTION( double qtable_conf_lower, (QTABLE, double) );
EXTERN_FUNCTION( double qtable_conf_upper, (QTABLE, double) );
EXTERN_FUNCTION( double qtable_conf_accuracy, (QTABLE, double) );
EXTERN_FUNCTION( double qtable_qlen, (QTABLE) );            /* ? */
EXTERN_FUNCTION( double qtable_qtime, (QTABLE) );           /* ? */
EXTERN_FUNCTION( double qtable_qtsum, (QTABLE) );           /* ? */

/*  legacy functions - prior to version 18  */

typedef struct qtble *QHIST;

EXTERN_FUNCTION( QHIST  create_qhistogram, (const char*, long) );
EXTERN_FUNCTION( void   set_moving_qtable, (QTABLE, long) );
EXTERN_FUNCTION( void   note_state, (QTABLE, long) );
EXTERN_FUNCTION( double current_state, (QTABLE) );
EXTERN_FUNCTION( long   max_qtables, (long) );
EXTERN_FUNCTION( double qhistogram_time, (QHIST) );
EXTERN_FUNCTION( double qhistogram_bucket_time, (QHIST, long) );
EXTERN_FUNCTION( long   qhistogram_num, (QHIST) );
EXTERN_FUNCTION( long   qhistogram_bucket_cnt, (QHIST, long) );
EXTERN_FUNCTION( long   qtable_cnt, (QTABLE) );
EXTERN_FUNCTION( long   qtable_cur, (QTABLE) );

/*----------------------------------------------------------------------------*/
/*   Meters                                                                   */
/*----------------------------------------------------------------------------*/

typedef struct mtr *METER;

EXTERN_FUNCTION( METER  create_meter, (const char*) );
EXTERN_FUNCTION( void   meter_histogram, (METER, long, double, double) );
EXTERN_FUNCTION( void   meter_confidence, (METER) );
EXTERN_FUNCTION( void   meter_run_length, (METER, double, double, double) );
EXTERN_FUNCTION( void   note_passage, (METER) );
EXTERN_FUNCTION( void   report_meter, (METER) );
EXTERN_FUNCTION( void   report_meters, (_VOID_) );
EXTERN_FUNCTION( void   meter_summary, (_VOID_) );
EXTERN_FUNCTION( void   reset_meter, (METER) );
EXTERN_FUNCTION( void	reset_meters, (_VOID_) );
EXTERN_FUNCTION( void   set_name_meter, (METER, const char*) );
EXTERN_FUNCTION( void   delete_meter, (METER) );
EXTERN_FUNCTION( char*	meter_name, (METER) );
EXTERN_FUNCTION( double meter_start_time, (METER) );
EXTERN_FUNCTION( long   meter_cnt, (METER) );
EXTERN_FUNCTION( double meter_rate, (METER) );
EXTERN_FUNCTION( TABLE  meter_ip_table, (METER) );

/*----------------------------------------------------------------------------*/
/*   Boxes                                                                    */
/*----------------------------------------------------------------------------*/

typedef struct bx * BOX;

EXTERN_FUNCTION( BOX    create_box, (const char*) );
EXTERN_FUNCTION( void   box_time_histogram, (BOX, long, double, double) );
EXTERN_FUNCTION( void   box_time_confidence, (BOX) );
EXTERN_FUNCTION( void   box_time_run_length, (BOX, double, double, double) );
EXTERN_FUNCTION( void   box_time_moving_window, (BOX, long) );
EXTERN_FUNCTION( void   box_number_histogram, (BOX, long, long, long) );
EXTERN_FUNCTION( void   box_number_confidence, (BOX) );
EXTERN_FUNCTION( void   box_number_run_length, (BOX, double, double, double) );
EXTERN_FUNCTION( void   box_number_moving_window, (BOX, long) );
EXTERN_FUNCTION( double enter_box, (BOX) );
EXTERN_FUNCTION( void   exit_box, (BOX, double) );
EXTERN_FUNCTION( void   report_box, (BOX) );
EXTERN_FUNCTION( void   report_boxes, (_VOID_) );
EXTERN_FUNCTION( void   box_summary, (_VOID_) );
EXTERN_FUNCTION( void   set_name_box, (BOX, const char*) );
EXTERN_FUNCTION( void   reset_box, (BOX) );
EXTERN_FUNCTION( void	reset_boxes, (_VOID_) );
EXTERN_FUNCTION( void   delete_box, (BOX) );
EXTERN_FUNCTION( char*	box_name, (BOX) );
EXTERN_FUNCTION( QTABLE box_number_qtable, (BOX) );
EXTERN_FUNCTION( TABLE  box_time_table, (BOX) );

/*----------------------------------------------------------------------------*/
/*   Simulation control / stats / tracing / error handling                    */
/*----------------------------------------------------------------------------*/

EXTERN_FUNCTION( void   set_model_name, (const char*) );
EXTERN_FUNCTION( void   monitor_csim, (_VOID_) );
EXTERN_FUNCTION( void   csim_reset, (_VOID_) );
EXTERN_FUNCTION( void   csim_rerun, (_VOID_) );
EXTERN_FUNCTION( void	set_conclude_flag, (_VOID_) );

EXTERN_FUNCTION( void   report_hdr, (_VOID_) );
EXTERN_FUNCTION( void   report, (_VOID_) );
EXTERN_FUNCTION( void   dump_status, (_VOID_) );
EXTERN_FUNCTION( void   mdlstat, (_VOID_) );

EXTERN_FUNCTION( void   trace_on, (_VOID_) );
EXTERN_FUNCTION( void   trace_off, (_VOID_) );
EXTERN_FUNCTION( void   trace_process, (const char *) );
EXTERN_FUNCTION( void   trace_object, (const char *) );
EXTERN_FUNCTION( void   trace_msg, (const char *) );
extern long trace_bma;

EXTERN_FUNCTION( double	cputime, (_VOID_) );
EXTERN_FUNCTION( char*	time_of_day, (_VOID_) );
EXTERN_FUNCTION( long   events_processed, (_VOID_) );

extern long initial_batch_size;
#ifndef __cplusplus
extern EVENT event_list_empty;
extern EVENT converged;
extern EVENT end_batch;
extern EVENT sim_terminated;
#endif

#ifdef __STDC__
typedef void (*EH)(long);     /* error handler function */
#else
typedef void (*EH)();
#endif

EXTERN_FUNCTION( void   set_err_handler, (EH) );
EXTERN_FUNCTION( void   clear_err_handler, (_VOID_) );
EXTERN_FUNCTION( void   print_csim_error, (long) );
EXTERN_FUNCTION( const char*  csim_error_msg, (long) );

EXTERN_FUNCTION( void   set_input_file, (FILE*) );
EXTERN_FUNCTION( void   set_output_file, (FILE*) );
EXTERN_FUNCTION( void   set_error_file, (FILE*) );
EXTERN_FUNCTION( void   set_trace_file, (FILE*) );

EXTERN_FUNCTION( void   proc_csim_args, (int*, char***) );
EXTERN_FUNCTION( void   conclude_csim, (_VOID_) );
EXTERN_FUNCTION( void	csim_exit, (long) );

EXTERN_FUNCTION( char*	do_malloc, (long) );
EXTERN_FUNCTION( void do_free, (char *) );
EXTERN_FUNCTION( char*	do_malloc_list, (long) );
EXTERN_FUNCTION( void do_free_list, (char *) );

/* stack copying operations on HP machines */

#ifdef HPPA
EXTERN_FUNCTION( long   get_stack_copy, (_VOID_) );
EXTERN_FUNCTION( long   get_stack_swap, (_VOID_) );
EXTERN_FUNCTION( long   get_stack_safe, (_VOID_) );
EXTERN_FUNCTION( long   get_stack_size, (_VOID_) );
EXTERN_FUNCTION( void   set_stack_copy, (_VOID_) );
EXTERN_FUNCTION( void   set_stack_swap, (_VOID_) );
EXTERN_FUNCTION( void   set_stack_save, (_VOID_) );
EXTERN_FUNCTION( void   set_stack_size, (_VOID_) );
#endif

extern long trsw;		/* for use by csim developers only */
extern long  _newPid;	/* id of newly created process */
extern long make_ctrl_proc;

#endif
