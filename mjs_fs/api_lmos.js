let LMOS = {
    _gsi: ffi("char* get_sys_info(void)"),
    _rb: ffi("void reboot(int)"),
    // ## **`getSysInfo()`**
    // Get system info 
    // Returned json if success or null if C function not exist.
    getSysInfo: function () {
        return JSON.parse(this._gsi());
    },
    // ## **`reboot(delay)`**
    // System reboot after delay miliseconds, default delay: 100
    reboot: function (delay) {
        this._rb(delay);
    },
};