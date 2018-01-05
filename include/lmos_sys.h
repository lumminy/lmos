#ifndef CS_MOS_LIBS_LMOS_SRC_MGOS_LMOS_H_
#define CS_MOS_LIBS_LMOS_SRC_MGOS_LMOS_H_

#include "mgos.h"

#include "mgos_system.h"
#include "mgos_net.h"
#include "mgos_timers.h"
#ifdef MGOS_HAVE_WIFI
#include "mgos_wifi.h"
#endif

typedef void (*lmos_callback)(char*,void *ud);
void get_sys_info(lmos_callback lmos_cb,void *ud);

bool mgos_lmos_init(void);
#endif