/*
 * Copyright 2010-2023 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU General Public License version 2
 * or later (GPLv2+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <stdint.h>

#define MAX_RESPAWN		100

extern GMainLoop *mainloop;
extern struct qb_ipcs_service_handlers pacemakerd_ipc_callbacks;
extern const char *pacemakerd_state;
extern gboolean running_with_sbd;
extern unsigned int shutdown_complete_state_reported_to;
extern gboolean shutdown_complete_state_reported_client_closed;
extern crm_trigger_t *shutdown_trigger;
extern crm_trigger_t *startup_trigger;
extern time_t subdaemon_check_progress;

gboolean pacemakerd_read_config(void);

gboolean cluster_connect_cfg(void);
void cluster_disconnect_cfg(void);
int find_and_track_existing_processes(void);
gboolean init_children_processes(void *user_data);
void restart_cluster_subdaemons(void);
void pcmk_shutdown(int nsig);
void pcmkd_shutdown_corosync(void);
bool pcmkd_corosync_connected(void);
