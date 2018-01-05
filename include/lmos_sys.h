typedef void (*lmos_callback)(char*,void *ud);
void get_sys_info(lmos_callback lmos_cb,void *ud);

bool mgos_lmos_init(void);