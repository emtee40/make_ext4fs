/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file is used to define the properties of the filesystem
** images generated by build tools (mkbootfs and mkyaffs2image) and
** by the device side of adb.
*/

#ifndef _ANDROID_FILESYSTEM_CONFIG_H_
#define _ANDROID_FILESYSTEM_CONFIG_H_

#include <string.h>
#include <sys/stat.h>
#include <stdint.h>

#ifdef HAVE_ANDROID_OS
#include <linux/capability.h>
#else
#include "android_filesystem_capability.h"
#endif
#define CAP_MASK_LONG(cap_name)  (1ULL << (cap_name))

/* This is the master Users and Groups config for the platform.
 * DO NOT EVER RENUMBER
 */

#define AID_ROOT 0 /* traditional unix root user */
#define AID_SYSTEM 1000 /* system server */
#define AID_RADIO 1001           /* telephony subsystem, RIL */
#define AID_BLUETOOTH 1002       /* bluetooth subsystem */
#define AID_GRAPHICS 1003        /* graphics devices */
#define AID_INPUT 1004           /* input devices */
#define AID_AUDIO 1005           /* audio devices */
#define AID_CAMERA 1006          /* camera devices */
#define AID_LOG 1007             /* log devices */
#define AID_COMPASS 1008         /* compass device */
#define AID_MOUNT 1009           /* mountd socket */
#define AID_WIFI 1010            /* wifi subsystem */
#define AID_ADB 1011             /* android debug bridge (adbd) */
#define AID_INSTALL 1012         /* group for installing packages */
#define AID_MEDIA 1013           /* mediaserver process */
#define AID_DHCP 1014            /* dhcp client */
#define AID_SDCARD_RW 1015       /* external storage write access */
#define AID_VPN 1016             /* vpn system */
#define AID_KEYSTORE 1017        /* keystore subsystem */
#define AID_USB 1018             /* USB devices */
#define AID_DRM 1019             /* DRM server */
#define AID_MDNSR 1020           /* MulticastDNSResponder (service discovery) */
#define AID_GPS 1021             /* GPS daemon */
#define AID_UNUSED1 1022         /* deprecated, DO NOT USE */
#define AID_MEDIA_RW 1023        /* internal media storage write access */
#define AID_MTP 1024             /* MTP USB driver access */
#define AID_UNUSED2 1025         /* deprecated, DO NOT USE */
#define AID_DRMRPC 1026          /* group for drm rpc */
#define AID_NFC 1027             /* nfc subsystem */
#define AID_SDCARD_R 1028        /* external storage read access */
#define AID_CLAT 1029            /* clat part of nat464 */
#define AID_LOOP_RADIO 1030      /* loop radio devices */
#define AID_MEDIA_DRM 1031       /* MediaDrm plugins */
#define AID_PACKAGE_INFO 1032    /* access to installed package details */
#define AID_SDCARD_PICS 1033     /* external storage photos access */
#define AID_SDCARD_AV 1034       /* external storage audio/video access */
#define AID_SDCARD_ALL 1035      /* access all users external storage */
#define AID_LOGD 1036            /* log daemon */
#define AID_SHARED_RELRO 1037    /* creator of shared GNU RELRO files */
#define AID_DBUS 1038            /* dbus-daemon IPC broker process */
#define AID_TLSDATE 1039         /* tlsdate unprivileged user */
#define AID_MEDIA_EX 1040        /* mediaextractor process */
#define AID_AUDIOSERVER 1041     /* audioserver process */
#define AID_METRICS_COLL 1042    /* metrics_collector process */
#define AID_METRICSD 1043        /* metricsd process */
#define AID_WEBSERV 1044         /* webservd process */
#define AID_DEBUGGERD 1045       /* debuggerd unprivileged user */
#define AID_MEDIA_CODEC 1046     /* mediacodec process */
#define AID_CAMERASERVER 1047    /* cameraserver process */
#define AID_FIREWALL 1048        /* firewalld process */
#define AID_TRUNKS 1049          /* trunksd process (TPM daemon) */
#define AID_NVRAM 1050           /* Access-controlled NVRAM */
#define AID_DNS 1051             /* DNS resolution daemon (system: netd) */
#define AID_DNS_TETHER 1052      /* DNS resolution daemon (tether: dnsmasq) */
#define AID_WEBVIEW_ZYGOTE 1053  /* WebView zygote process */
#define AID_VEHICLE_NETWORK 1054 /* Vehicle network service */
#define AID_MEDIA_AUDIO 1055     /* GID for audio files on internal media storage */
#define AID_MEDIA_VIDEO 1056     /* GID for video files on internal media storage */
#define AID_MEDIA_IMAGE 1057     /* GID for image files on internal media storage */
#define AID_TOMBSTONED 1058      /* tombstoned user */
#define AID_MEDIA_OBB 1059       /* GID for OBB files on internal media storage */
#define AID_ESE 1060             /* embedded secure element (eSE) subsystem */
#define AID_OTA_UPDATE 1061      /* resource tracking UID for OTA updates */
/* Changes to this file must be made in AOSP, *not* in internal branches. */
#define AID_SHELL 2000 /* adb and debug shell user */
#define AID_CACHE 2001 /* cache access */
#define AID_DIAG 2002  /* access to diagnostic resources */
/* The range 2900-2999 is reserved for OEM, and must never be
 * used here */
#define AID_OEM_RESERVED_START 2900
#define AID_OEM_RESERVED_END 2999
/* The 3000 series are intended for use as supplemental group id's only.
 * They indicate special Android capabilities that the kernel is aware of. */
#define AID_NET_BT_ADMIN 3001 /* bluetooth: create any socket */
#define AID_NET_BT 3002       /* bluetooth: create sco, rfcomm or l2cap sockets */
#define AID_INET 3003         /* can create AF_INET and AF_INET6 sockets */
#define AID_NET_RAW 3004      /* can create raw INET sockets */
#define AID_NET_ADMIN 3005    /* can configure interfaces and routing tables. */
#define AID_NET_BW_STATS 3006 /* read bandwidth statistics */
#define AID_NET_BW_ACCT 3007  /* change bandwidth statistics accounting */
#define AID_READPROC 3009     /* Allow /proc read access */
#define AID_WAKELOCK 3010     /* Allow system wakelock read/write access */
/* The range 5000-5999 is also reserved for OEM, and must never be used here. */
#define AID_OEM_RESERVED_2_START 5000
#define AID_OEM_RESERVED_2_END 5999
#define AID_EVERYBODY 9997 /* shared between all apps in the same profile */
#define AID_MISC 9998      /* access to misc storage */
#define AID_NOBODY 9999
#define AID_APP 10000       /* TODO: switch users over to AID_APP_START */
#define AID_APP_START 10000 /* first app user */
#define AID_APP_END 19999   /* last app user */
#define AID_CACHE_GID_START 20000 /* start of gids for apps to mark cached data */
#define AID_CACHE_GID_END 29999   /* end of gids for apps to mark cached data */
#define AID_EXT_GID_START 30000 /* start of gids for apps to mark external data */
#define AID_EXT_GID_END 39999   /* end of gids for apps to mark external data */
#define AID_EXT_CACHE_GID_START 40000 /* start of gids for apps to mark external cached data */
#define AID_EXT_CACHE_GID_END 49999   /* end of gids for apps to mark external cached data */
#define AID_SHARED_GID_START 50000 /* start of gids for apps in each user to share */
#define AID_SHARED_GID_END 59999   /* end of gids for apps in each user to share */
#define AID_ISOLATED_START 99000 /* start of uids for fully isolated sandboxed processes */
#define AID_ISOLATED_END 99999   /* end of uids for fully isolated sandboxed processes */
#define AID_USER 100000        /* TODO: switch users over to AID_USER_OFFSET */
#define AID_USER_OFFSET 100000 /* offset for uid ranges for each user */

#if !defined(EXCLUDE_FS_CONFIG_STRUCTURES)
struct android_id_info {
    const char *name;
    unsigned aid;
};

static const struct android_id_info android_ids[] = {
    { "root",          AID_ROOT, },

    { "system",        AID_SYSTEM, },

    { "radio",         AID_RADIO, },
    { "bluetooth",     AID_BLUETOOTH, },
    { "graphics",      AID_GRAPHICS, },
    { "input",         AID_INPUT, },
    { "audio",         AID_AUDIO, },
    { "camera",        AID_CAMERA, },
    { "log",           AID_LOG, },
    { "compass",       AID_COMPASS, },
    { "mount",         AID_MOUNT, },
    { "wifi",          AID_WIFI, },
    { "adb",           AID_ADB, },
    { "install",       AID_INSTALL, },
    { "media",         AID_MEDIA, },
    { "dhcp",          AID_DHCP, },
    { "sdcard_rw",     AID_SDCARD_RW, },
    { "vpn",           AID_VPN, },
    { "keystore",      AID_KEYSTORE, },
    { "usb",           AID_USB, },
    { "drm",           AID_DRM, },
    { "mdnsr",         AID_MDNSR, },
    { "gps",           AID_GPS, },
    // AID_UNUSED1
    { "media_rw",      AID_MEDIA_RW, },
    { "mtp",           AID_MTP, },
    // AID_UNUSED2
    { "drmrpc",        AID_DRMRPC, },
    { "nfc",           AID_NFC, },
    { "sdcard_r",      AID_SDCARD_R, },
    { "clat",          AID_CLAT, },
    { "loop_radio",    AID_LOOP_RADIO, },
    { "mediadrm",      AID_MEDIA_DRM, },
    { "package_info",  AID_PACKAGE_INFO, },
    { "sdcard_pics",   AID_SDCARD_PICS, },
    { "sdcard_av",     AID_SDCARD_AV, },
    { "sdcard_all",    AID_SDCARD_ALL, },
    { "logd",          AID_LOGD, },
    { "shared_relro",  AID_SHARED_RELRO, },
    { "dbus",          AID_DBUS, },
    { "tlsdate",       AID_TLSDATE, },
    { "mediaex",       AID_MEDIA_EX, },
    { "audioserver",   AID_AUDIOSERVER, },
    { "metrics_coll",  AID_METRICS_COLL },
    { "metricsd",      AID_METRICSD },
    { "webserv",       AID_WEBSERV },
    { "debuggerd",     AID_DEBUGGERD, },
    { "mediacodec",    AID_MEDIA_CODEC, },
    { "cameraserver",  AID_CAMERASERVER, },
    { "firewall",      AID_FIREWALL, },
    { "trunks",        AID_TRUNKS, },
    { "nvram",         AID_NVRAM, },
    { "dns",           AID_DNS, },
    { "dns_tether",    AID_DNS_TETHER, },
    { "webview_zygote", AID_WEBVIEW_ZYGOTE, },
    { "vehicle_network", AID_VEHICLE_NETWORK, },
    { "media_audio",   AID_MEDIA_AUDIO, },
    { "media_video",   AID_MEDIA_VIDEO, },
    { "media_image",   AID_MEDIA_IMAGE, },

    { "shell",         AID_SHELL, },
    { "cache",         AID_CACHE, },
    { "diag",          AID_DIAG, },

    { "net_bt_admin",  AID_NET_BT_ADMIN, },
    { "net_bt",        AID_NET_BT, },
    { "inet",          AID_INET, },
    { "net_raw",       AID_NET_RAW, },
    { "net_admin",     AID_NET_ADMIN, },
    { "net_bw_stats",  AID_NET_BW_STATS, },
    { "net_bw_acct",   AID_NET_BW_ACCT, },
    { "readproc",      AID_READPROC, },
    { "wakelock",      AID_WAKELOCK, },

    { "everybody",     AID_EVERYBODY, },
    { "misc",          AID_MISC, },
    { "nobody",        AID_NOBODY, },
    { "tombstoned",	AID_TOMBSTONED },
    { "media_obb",	AID_MEDIA_OBB },
    { "ese",	AID_ESE },
    { "ota_update",	AID_OTA_UPDATE },
    { "shell",	AID_SHELL },
    { "cache",	AID_CACHE },
    { "diag",	AID_DIAG },
    { "oem_reserved_start",	AID_OEM_RESERVED_START },
    { "oem_reserved_end",	AID_OEM_RESERVED_END },
    { "net_bt_admin",	AID_NET_BT_ADMIN },
    { "net_bt",	AID_NET_BT },
    { "inet",	AID_INET },
    { "net_raw",	AID_NET_RAW },
    { "net_admin",	AID_NET_ADMIN },
    { "net_bw_stats",	AID_NET_BW_STATS },
    { "net_bw_acct",	AID_NET_BW_ACCT },
    { "readproc",	AID_READPROC },
    { "wakelock",	AID_WAKELOCK },
    { "oem_reserved_2_start",	AID_OEM_RESERVED_2_START },
    { "oem_reserved_2_end",	AID_OEM_RESERVED_2_END },
    { "everybody",	AID_EVERYBODY },
    { "misc",	AID_MISC },
    { "nobody",	AID_NOBODY },
    { "app",	AID_APP },
    { "app_start",	AID_APP_START },
    { "app_end",	AID_APP_END },
    { "cache_gid_start",	AID_CACHE_GID_START },
    { "cache_gid_end",	AID_CACHE_GID_END },
    { "ext_gid_start",	AID_EXT_GID_START },
    { "ext_gid_end",	AID_EXT_GID_END },
    { "ext_cache_gid_start",	AID_EXT_CACHE_GID_START },
    { "ext_cache_gid_end",	AID_EXT_CACHE_GID_END },
    { "shared_gid_start",	AID_SHARED_GID_START },
    { "shared_gid_end",	AID_SHARED_GID_END },
    { "isolated_start",	AID_ISOLATED_START },
    { "isolated_end",	AID_ISOLATED_END },
    { "user",	AID_USER },
    { "user_offset",	AID_USER_OFFSET },
};

#define android_id_count \
    (sizeof(android_ids) / sizeof(android_ids[0]))

struct fs_path_config {
    unsigned mode;
    unsigned uid;
    unsigned gid;
    uint64_t capabilities;
    const char *prefix;
};

/* Rules for directories.
** These rules are applied based on "first match", so they
** should start with the most specific path and work their
** way up to the root.
*/

static const struct fs_path_config android_dirs[] = {
    /* clang-format off */
    { 00770, AID_SYSTEM,       AID_CACHE,        0, "cache" },
    { 00500, AID_ROOT,         AID_ROOT,         0, "config" },
    { 00771, AID_SYSTEM,       AID_SYSTEM,       0, "data/app" },
    { 00771, AID_SYSTEM,       AID_SYSTEM,       0, "data/app-private" },
    { 00771, AID_SYSTEM,       AID_SYSTEM,       0, "data/app-ephemeral" },
    { 00771, AID_ROOT,         AID_ROOT,         0, "data/dalvik-cache" },
    { 00771, AID_SYSTEM,       AID_SYSTEM,       0, "data/data" },
    { 00771, AID_SHELL,        AID_SHELL,        0, "data/local/tmp" },
    { 00771, AID_SHELL,        AID_SHELL,        0, "data/local" },
    { 00770, AID_DHCP,         AID_DHCP,         0, "data/misc/dhcp" },
    { 00771, AID_SHARED_RELRO, AID_SHARED_RELRO, 0, "data/misc/shared_relro" },
    { 01771, AID_SYSTEM,       AID_MISC,         0, "data/misc" },
    { 00775, AID_MEDIA_RW,     AID_MEDIA_RW,     0, "data/media/Music" },
    { 00775, AID_MEDIA_RW,     AID_MEDIA_RW,     0, "data/media" },
    { 00750, AID_ROOT,         AID_SHELL,        0, "data/nativetest" },
    { 00750, AID_ROOT,         AID_SHELL,        0, "data/nativetest64" },
    { 00775, AID_ROOT,         AID_ROOT,         0, "data/preloads" },
    { 00771, AID_SYSTEM,       AID_SYSTEM,       0, "data" },
    { 00755, AID_ROOT,         AID_SYSTEM,       0, "mnt" },
    { 00755, AID_ROOT,         AID_ROOT,         0, "root" },
    { 00750, AID_ROOT,         AID_SHELL,        0, "sbin" },
    { 00777, AID_ROOT,         AID_ROOT,         0, "sdcard" },
    { 00751, AID_ROOT,         AID_SDCARD_R,     0, "storage" },
    { 00755, AID_ROOT,         AID_SHELL,        0, "system/bin" },
    { 00755, AID_ROOT,         AID_ROOT,         0, "system/etc/ppp" },
    { 00755, AID_ROOT,         AID_SHELL,        0, "system/vendor" },
    { 00755, AID_ROOT,         AID_SHELL,        0, "system/xbin" },
    { 00755, AID_ROOT,         AID_SHELL,        0, "vendor" },
    { 00755, AID_ROOT,         AID_ROOT,         0, 0 },
    /* clang-format on */
};
/* Rules for files.
** These rules are applied based on "first match", so they
** should start with the most specific path and work their
** way up to the root. Prefixes ending in * denotes wildcard
** and will allow partial matches.
*/
static const char sys_conf_dir[] = "/system/etc/fs_config_dirs";
static const char sys_conf_file[] = "/system/etc/fs_config_files";
/* No restrictions are placed on the vendor and oem file-system config files,
 * although the developer is advised to restrict the scope to the /vendor or
 * oem/ file-system since the intent is to provide support for customized
 * portions of a separate vendor.img or oem.img.  Has to remain open so that
 * customization can also land on /system/vendor, /system/oem or /system/odm.
 * We expect build-time checking or filtering when constructing the associated
 * fs_config_* files (see build/tools/fs_config/fs_config_generate.c)
 */
static const char ven_conf_dir[] = "/vendor/etc/fs_config_dirs";
static const char ven_conf_file[] = "/vendor/etc/fs_config_files";
static const char oem_conf_dir[] = "/oem/etc/fs_config_dirs";
static const char oem_conf_file[] = "/oem/etc/fs_config_files";
static const char odm_conf_dir[] = "/odm/etc/fs_config_dirs";
static const char odm_conf_file[] = "/odm/etc/fs_config_files";
static const char* conf[][2] = {
    {sys_conf_file, sys_conf_dir},
    {ven_conf_file, ven_conf_dir},
    {oem_conf_file, oem_conf_dir},
    {odm_conf_file, odm_conf_dir},
};
static const struct fs_path_config android_files[] = {
    /* clang-format off */
    { 00644, AID_SYSTEM,    AID_SYSTEM,    0, "data/app/*" },
    { 00644, AID_SYSTEM,    AID_SYSTEM,    0, "data/app-ephemeral/*" },
    { 00644, AID_SYSTEM,    AID_SYSTEM,    0, "data/app-private/*" },
    { 00644, AID_APP,       AID_APP,       0, "data/data/*" },
    { 00644, AID_MEDIA_RW,  AID_MEDIA_RW,  0, "data/media/*" },
    { 00640, AID_ROOT,      AID_SHELL,     0, "data/nativetest/tests.txt" },
    { 00640, AID_ROOT,      AID_SHELL,     0, "data/nativetest64/tests.txt" },
    { 00750, AID_ROOT,      AID_SHELL,     0, "data/nativetest/*" },
    { 00750, AID_ROOT,      AID_SHELL,     0, "data/nativetest64/*" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "default.prop" }, // legacy
    { 00600, AID_ROOT,      AID_ROOT,      0, "system/etc/prop.default" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "odm/build.prop" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "odm/default.prop" },
    { 00444, AID_ROOT,      AID_ROOT,      0, odm_conf_dir + 1 },
    { 00444, AID_ROOT,      AID_ROOT,      0, odm_conf_file + 1 },
    { 00600, AID_ROOT,      AID_ROOT,      0, "system/odm/build.prop" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "system/odm/default.prop" },
    { 00444, AID_ROOT,      AID_ROOT,      0, "system/odm/etc/fs_config_dirs" },
    { 00444, AID_ROOT,      AID_ROOT,      0, "system/odm/etc/fs_config_files" },
    { 00444, AID_ROOT,      AID_ROOT,      0, oem_conf_dir + 1 },
    { 00444, AID_ROOT,      AID_ROOT,      0, oem_conf_file + 1 },
    { 00444, AID_ROOT,      AID_ROOT,      0, "system/oem/etc/fs_config_dirs" },
    { 00444, AID_ROOT,      AID_ROOT,      0, "system/oem/etc/fs_config_files" },
    { 00750, AID_ROOT,      AID_SHELL,     0, "sbin/fs_mgr" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/bin/crash_dump32" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/bin/crash_dump64" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/bin/debuggerd" },
    { 00750, AID_ROOT,      AID_ROOT,      0, "system/bin/install-recovery.sh" },
    { 00700, AID_ROOT,      AID_ROOT,      0, "system/bin/secilc" },
    { 00750, AID_ROOT,      AID_ROOT,      0, "system/bin/uncrypt" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "system/build.prop" },
    { 00000, AID_ROOT,      AID_ROOT,      0, sys_conf_dir + 1 },
    { 00444, AID_ROOT,      AID_ROOT,      0, sys_conf_file + 1 },
    { 00440, AID_ROOT,      AID_SHELL,     0, "system/etc/init.goldfish.rc" },
    { 00550, AID_ROOT,      AID_SHELL,     0, "system/etc/init.goldfish.sh" },
    { 00550, AID_ROOT,      AID_SHELL,     0, "system/etc/init.ril" },
    { 00555, AID_ROOT,      AID_ROOT,      0, "system/etc/ppp/*" },
    { 00555, AID_ROOT,      AID_ROOT,      0, "system/etc/rc.*" },
    { 00440, AID_ROOT,      AID_ROOT,      0, "system/etc/recovery.img" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "system/vendor/build.prop" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "system/vendor/default.prop" },
    { 00444, AID_ROOT,      AID_ROOT,      0, "system/vendor/etc/fs_config_dirs" },
    { 00444, AID_ROOT,      AID_ROOT,      0, "system/vendor/etc/fs_config_files" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "vendor/build.prop" },
    { 00600, AID_ROOT,      AID_ROOT,      0, "vendor/default.prop" },
    { 00444, AID_ROOT,      AID_ROOT,      0, ven_conf_dir + 1 },
    { 00444, AID_ROOT,      AID_ROOT,      0, ven_conf_file + 1 },
    /* the following two files are INTENTIONALLY set-uid, but they
     * are NOT included on user builds. */
    { 06755, AID_ROOT,      AID_ROOT,      0, "system/xbin/procmem" },
    { 04750, AID_ROOT,      AID_SHELL,     0, "system/xbin/su" },
    
    /* the following files have enhanced capabilities and ARE included
     * in user builds. */
    { 00700, AID_SYSTEM,    AID_SHELL,     CAP_MASK_LONG(CAP_BLOCK_SUSPEND),
                                              "system/bin/inputflinger" },
    { 00550, AID_LOGD,      AID_LOGD,      CAP_MASK_LONG(CAP_SYSLOG) |
                                           CAP_MASK_LONG(CAP_AUDIT_CONTROL) |
                                           CAP_MASK_LONG(CAP_SETGID),
                                              "system/bin/logd" },
    { 00750, AID_ROOT,      AID_SHELL,     CAP_MASK_LONG(CAP_SETUID) |
                                           CAP_MASK_LONG(CAP_SETGID),
                                              "system/bin/run-as" },
    /* Support FIFO scheduling mode in SurfaceFlinger. */
    { 00755, AID_SYSTEM,    AID_GRAPHICS,  CAP_MASK_LONG(CAP_SYS_NICE),
                                              "system/bin/surfaceflinger" },
    /* Support hostapd administering a network interface. */
    { 00755, AID_WIFI,      AID_WIFI,      CAP_MASK_LONG(CAP_NET_ADMIN) |
                                           CAP_MASK_LONG(CAP_NET_RAW),
                                              "system/vendor/bin/hostapd" },
    { 00755, AID_WIFI,      AID_WIFI,      CAP_MASK_LONG(CAP_NET_ADMIN) |
                                           CAP_MASK_LONG(CAP_NET_RAW),
                                              "vendor/bin/hostapd" },
    /* Support Bluetooth legacy hal accessing /sys/class/rfkill
     * Support RT scheduling in Bluetooth */
    { 00700, AID_BLUETOOTH, AID_BLUETOOTH, CAP_MASK_LONG(CAP_NET_ADMIN) |
                                           CAP_MASK_LONG(CAP_SYS_NICE),
                                              "system/vendor/bin/hw/android.hardware.bluetooth@1.0-service" },
    { 00700, AID_BLUETOOTH, AID_BLUETOOTH, CAP_MASK_LONG(CAP_NET_ADMIN) |
                                           CAP_MASK_LONG(CAP_SYS_NICE),
                                              "vendor/bin/hw/android.hardware.bluetooth@1.0-service" },
    /* Support wifi_hal_legacy administering a network interface. */
    { 00755, AID_WIFI,      AID_WIFI,      CAP_MASK_LONG(CAP_NET_ADMIN) |
                                           CAP_MASK_LONG(CAP_NET_RAW),
                                              "system/vendor/bin/hw/android.hardware.wifi@1.0-service" },
    { 00755, AID_WIFI,      AID_WIFI,      CAP_MASK_LONG(CAP_NET_ADMIN) |
                                           CAP_MASK_LONG(CAP_NET_RAW),
                                              "vendor/bin/hw/android.hardware.wifi@1.0-service" },
    /* A non-privileged zygote that spawns
     * isolated processes for web rendering. */
    { 0750,  AID_ROOT,      AID_ROOT,      CAP_MASK_LONG(CAP_SETUID) |
                                           CAP_MASK_LONG(CAP_SETGID) |
                                           CAP_MASK_LONG(CAP_SETPCAP),
                                              "system/bin/webview_zygote32" },
    { 0750,  AID_ROOT,      AID_ROOT,      CAP_MASK_LONG(CAP_SETUID) |
                                           CAP_MASK_LONG(CAP_SETGID) |
                                           CAP_MASK_LONG(CAP_SETPCAP),
                                              "system/bin/webview_zygote64" },
    /* generic defaults */
    { 00755, AID_ROOT,      AID_ROOT,      0, "bin/*" },
    { 00640, AID_ROOT,      AID_SHELL,     0, "fstab.*" },
    { 00750, AID_ROOT,      AID_SHELL,     0, "init*" },
    { 00750, AID_ROOT,      AID_SHELL,     0, "sbin/*" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/bin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      0, "system/lib/valgrind/*" },
    { 00755, AID_ROOT,      AID_ROOT,      0, "system/lib64/valgrind/*" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/vendor/bin/*" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/vendor/xbin/*" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "system/xbin/*" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "vendor/bin/*" },
    { 00755, AID_ROOT,      AID_SHELL,     0, "vendor/xbin/*" },
    { 00644, AID_ROOT,      AID_ROOT,      0, 0 },
    /* clang-format on */
};

static void fs_config(const char *path, int dir,
                             unsigned *uid, unsigned *gid, unsigned *mode, uint64_t *capabilities)
{

    if (path[0] == '/') {
        path++;
    }

    const struct fs_path_config * pc = dir ? android_dirs : android_files;
    int plen = strlen(path);
    for(; pc->prefix; pc++){
        int len = strlen(pc->prefix);
        if (dir) {
            if(plen < len) continue;
            if(!strncmp(pc->prefix, path, len)) break;
            continue;
        }
        /* If name ends in * then allow partial matches. */
        if (pc->prefix[len -1] == '*') {
            if(!strncmp(pc->prefix, path, len - 1)) break;
        } else if (plen == len){
            if(!strncmp(pc->prefix, path, len)) break;
        }
    }
    *uid = pc->uid;
    *gid = pc->gid;
    *mode = (*mode & (~07777)) | pc->mode;
    *capabilities = pc->capabilities;

#if 0
    fprintf(stderr,"< '%s' '%s' %d %d %o >\n",
            path, pc->prefix ? pc->prefix : "", *uid, *gid, *mode);
#endif
}
#endif
#endif
