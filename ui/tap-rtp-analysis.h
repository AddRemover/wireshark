/* tap-rtp-analysis.h
 * RTP analysis addition for Wireshark
 *
 * Copyright 2003, Alcatel Business Systems
 * By Lars Ruoff <lars.ruoff@gmx.net>
 *
 * based on tap_rtp.c
 * Copyright 2003, Iskratel, Ltd, Kranj
 * By Miha Jemec <m.jemec@iskratel.si>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef __TAP_RTP_ANALYSIS_H__
#define __TAP_RTP_ANALYSIS_H__

#include <epan/address.h>
#include <epan/packet_info.h>

/** @file
 *  ???
 *  @todo what's this?
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************************************************************/
/* structure that holds the information about the forward and reversed direction */
typedef struct _bw_history_item {
    double time;
    guint32 bytes;
} bw_history_item;

#define BUFF_BW 300

typedef struct _tap_rtp_stat_t {
    gboolean        first_packet; /**< do not use in code that is called after rtppacket_analyse */
                               /* use (flags & STAT_FLAG_FIRST) instead */
    /* all of the following fields will be initialized after
     * rtppacket_analyse has been called
     */
    guint32         flags;      /* see STAT_FLAG-defines below */
    guint16         seq_num;
    guint32         timestamp;
    guint32         first_timestamp;
    double          bandwidth;
    bw_history_item bw_history[BUFF_BW];
    guint16         bw_start_index;
    guint16         bw_index;
    guint32         total_bytes;
    guint32         clock_rate;
    double          delta;
    double          jitter;
    double          diff;
    double          skew;
    double          sumt;
    double          sumTS;
    double          sumt2;
    double          sumtTS;
    double          time;       /**< Unit is ms */
    double          start_time; /**< Unit is ms */
    double          lastnominaltime;
    double          max_delta;
    double          max_jitter;
    double          max_skew;
    double          mean_jitter;
    guint32         max_nr;
    guint16         start_seq_nr;
    guint16         stop_seq_nr;
    guint32         total_nr;
    guint32         sequence;
    gboolean        under;
    gint            seq_cycles;
    guint16         pt;
    int             reg_pt;
    guint32         first_packet_num;
    guint           last_payload_len;
} tap_rtp_stat_t;

typedef struct _tap_rtp_save_data_t {
    guint32 timestamp;
    unsigned int payload_type;
    size_t payload_len;
} tap_rtp_save_data_t;

#define PT_UNDEFINED -1

/* status flags for the flags parameter in tap_rtp_stat_t */
#define STAT_FLAG_FIRST             0x001
#define STAT_FLAG_MARKER            0x002
#define STAT_FLAG_WRONG_SEQ         0x004
#define STAT_FLAG_PT_CHANGE         0x008
#define STAT_FLAG_PT_CN             0x010
#define STAT_FLAG_FOLLOW_PT_CN      0x020
#define STAT_FLAG_REG_PT_CHANGE     0x040
#define STAT_FLAG_WRONG_TIMESTAMP   0x080
#define STAT_FLAG_PT_T_EVENT        0x100
#define STAT_FLAG_DUP_PKT           0x200

/* forward */
struct _rtp_info;

/* function for analysing an RTP packet. Called from rtp_analysis and rtp_streams */
extern void rtppacket_analyse(tap_rtp_stat_t *statinfo,
                              packet_info *pinfo,
                              const struct _rtp_info *rtpinfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TAP_RTP_ANALYSIS_H__ */
