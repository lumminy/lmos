#include "mgos_system.h"
#include "mgos_net.h"
#include "mgos_timers.h"
#ifdef MGOS_HAVE_WIFI
#include "mgos_wifi.h"
#endif

#include "lmos_sys.h"

#if MGOS_ENABLE_SYS_SERVICE
void get_sys_info(lmos_callback lmos_cb, void *ud) {
          struct mgos_net_ip_info ip_info;
  memset(&ip_info, 0, sizeof(ip_info));
#ifdef MGOS_HAVE_WIFI
  char *status = mgos_wifi_get_status_str();
  char *ssid = mgos_wifi_get_connected_ssid();
  char sta_ip[16], ap_ip[16];
  memset(sta_ip, 0, sizeof(sta_ip));
  memset(ap_ip, 0, sizeof(ap_ip));
  if (mgos_net_get_ip_info(MGOS_NET_IF_TYPE_WIFI, MGOS_NET_IF_WIFI_STA,
                           &ip_info)) {
    mgos_net_ip_to_str(&ip_info.ip, sta_ip);
  }
  if (mgos_net_get_ip_info(MGOS_NET_IF_TYPE_WIFI, MGOS_NET_IF_WIFI_AP,
                           &ip_info)) {
    mgos_net_ip_to_str(&ip_info.ip, ap_ip);
  }
#endif
#ifdef MGOS_HAVE_ETHERNET
  char eth_ip[16];
  memset(eth_ip, 0, sizeof(eth_ip));
  if (mgos_net_get_ip_info(MGOS_NET_IF_TYPE_ETHERNET, 0, &ip_info)) {
    mgos_net_ip_to_str(&ip_info.ip, eth_ip);
  }
#endif
  (void) ip_info;

    //JSON struct
    char* json = "{app: \"%s\", fw_version: \"%s\", fw_id: \"%s\", mac: \"%s\", "
      "arch: \"%s\", uptime: %lu, "
      "ram_size: %d, ram_free: %d, ram_min_free: %d, "
      "fs_size: %d, fs_free: %d"
#ifdef MGOS_HAVE_WIFI
      ",wifi: {sta_ip: \"%s\", ap_ip: \"%s\", status: \"%s\", ssid: \"%s\"}"
#endif
#ifdef MGOS_HAVE_ETHERNET
      ",eth: {ip: \"%s\"}"
#endif
      "}";

    size_t needed = snprintf(NULL, 0, json, MGOS_APP, mgos_sys_ro_vars_get_fw_version(), mgos_sys_ro_vars_get_fw_id(),
      mgos_sys_ro_vars_get_mac_address(), mgos_sys_ro_vars_get_arch(),
      (unsigned long) mgos_uptime(), mgos_get_heap_size(),
      mgos_get_free_heap_size(), mgos_get_min_free_heap_size(),
      mgos_get_fs_size(), mgos_get_free_fs_size()
#ifdef MGOS_HAVE_WIFI
                              ,
      sta_ip, ap_ip, status == NULL ? "" : status, ssid == NULL ? "" : ssid
#endif
#ifdef MGOS_HAVE_ETHERNET
      ,
      eth_ip
#endif
      );

    char* json_str = (char*)malloc(needed * sizeof(char));

    sprintf(json_str, json, MGOS_APP, mgos_sys_ro_vars_get_fw_version(), mgos_sys_ro_vars_get_fw_id(),
      mgos_sys_ro_vars_get_mac_address(), mgos_sys_ro_vars_get_arch(),
      (unsigned long) mgos_uptime(), mgos_get_heap_size(),
      mgos_get_free_heap_size(), mgos_get_min_free_heap_size(),
      mgos_get_fs_size(), mgos_get_free_fs_size()
#ifdef MGOS_HAVE_WIFI
                              ,
      sta_ip, ap_ip, status == NULL ? "" : status, ssid == NULL ? "" : ssid
#endif
#ifdef MGOS_HAVE_ETHERNET
      ,
      eth_ip
#endif
      );

      (*lmos_cb)(json_str, ud);

#ifdef MGOS_HAVE_WIFI
  free(ssid);
  free(status);
#endif
      free(json_str);
      (void)ud;
      (void)lmos_cb;
}
#endif

bool mgos_lmos_init(void) { 
      return true; 
}