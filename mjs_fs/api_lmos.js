let LMOS = {
    getSysInfo: ffi("void get_sys_info(void(*)(char*,userdata),userdata)")
};